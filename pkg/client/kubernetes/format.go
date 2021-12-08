/*
 * Copyright (c) 2019 Huawei Technologies Co., Ltd.
 * MeshAccelerating is licensed under the Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *     http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
 * PURPOSE.
 * See the Mulan PSL v2 for more details.
 * Author: LemmyHuang
 * Create: 2021-10-09
 */

package kubernetes

// #cgo CFLAGS: -I../../../bpf/include
// #include "listener_type.h"
import "C"
import (
	"fmt"
	apiCoreV1 "k8s.io/api/core/v1"
	"openeuler.io/mesh/pkg/bpf/maps"
	"openeuler.io/mesh/pkg/nets"
	"openeuler.io/mesh/pkg/option"
)

var (
	convert = maps.NewConvertMapKey()
	// k = nodeName
	nodesMap = make(map[string]*apiCoreV1.Node)
)

type ClientEvent struct {
	Key			EventKey
	Service		*apiCoreV1.Service
	Endpoints	[]*apiCoreV1.Endpoints

	// k = endpointPort, v = count
	serviceCount	map[uint32]uint32
	// k = clusterPort, v = count
	endpointsCount	map[uint32]uint32
	// When you want to delete endpoint from the map,
	// you need to convert the address to key first.
	endpointsAddressToMapKey map[maps.GoAddress]maps.GoMapKey
}

type EventKey struct {
	opt		string
	name	string
}

var (
	ProtocolStrToC = map[apiCoreV1.Protocol]uint32 {
		apiCoreV1.ProtocolTCP:	0, //C.IPPROTO_TCP,
		apiCoreV1.ProtocolUDP:	6, //C.IPPROTO_UDP,
	}
)

func (event *ClientEvent) Init() {
	if event.serviceCount == nil {
		event.serviceCount = make(map[uint32]uint32)
	}
	if event.endpointsCount == nil {
		event.endpointsCount = make(map[uint32]uint32)
	}
	if event.endpointsAddressToMapKey == nil {
		event.endpointsAddressToMapKey = make(map[maps.GoAddress]maps.GoMapKey)
	}
}

func (event *ClientEvent) Reset() {
	event.Service = nil
	event.Endpoints = nil
}

func (event *ClientEvent) Empty() bool {
	for _, c := range event.serviceCount {
		if c > 0 {
			return true
		}
	}
	for _, c := range event.endpointsCount {
		if c > 0 {
			return true
		}
	}

	return false
}

func (event *ClientEvent) PrintDebug() {
	for _, ep := range event.Endpoints {
		log.Debugf("ClientEvent Endpoints: %#v", ep)
		log.Debug("------------------------------------")
	}

	if event.Service != nil {
		log.Debugf("ClientEvent Service: %#v", event.Service)
		log.Debug("------------------------------------")
	}

	for _, node := range nodesMap {
		log.Debugf("ClientEvent node: %#v", node)
		log.Debug("------------------------------------")
	}
}

func (event *ClientEvent) EventHandler() error {
	event.Init()
	// FIXME: if mapKey.Port change
	switch event.Key.opt {
	case InformerOptAdd:
		if err := event.addEndpoint(); err != nil {
			return err
		}
		if err := event.addCluster(); err != nil {
			return err
		}
		if err := event.addListener(); err != nil {
			return err
		}
	case InformerOptUpdate:
		if err := event.UpdateEndpoint(); err != nil {
			return err
		}
		if err := event.UpdateCluster(); err != nil {
			return err
		}
		if err := event.UpdateListener(); err != nil {
			return err
		}
	case InformerOptDelete:
		if err := event.DeleteListener(); err != nil {
			return err
		}
		if err := event.DeleteCluster(); err != nil {
			return err
		}
		if err := event.DeleteEndpoint(); err != nil {
			return err
		}
	default:
		return fmt.Errorf("eventAddItem get invalid informer opt")
	}

	//event.PrintDebug()
	return nil
}

func (event *ClientEvent) addEndpoint() error {
	var (
		mapKey maps.GoMapKey
		goEndpoint maps.GoEndpoint
		goLoadbalance maps.GoLoadbalance
	)

	mapKey.NameID = convert.StrToNum(event.Key.name)

	for _, ep := range event.Endpoints {
		for _, sub := range ep.Subsets {
			for _, epPort := range sub.Ports {
				if !option.EnabledProtocolConfig(string(epPort.Protocol)) {
					continue
				}

				goEndpoint.Address.Protocol = ProtocolStrToC[epPort.Protocol]
				goEndpoint.Address.Port = nets.ConvertPortToLittleEndian(epPort.Port)

				mapKey.Port = goEndpoint.Address.Port
				mapKey.Index = event.endpointsCount[mapKey.Port]

				for _, epAddr := range sub.Addresses {
					goEndpoint.Address.IPv4 = nets.ConvertIpToUint32(epAddr.IP)

					cEndpoint := goEndpoint.ToClang()
					if err := cEndpoint.Update(&mapKey); err != nil {
						event.DeleteEndpoint()
						return fmt.Errorf("add endpoint failed, %v, %s", mapKey, err)
					}

					goLoadbalance.MapKey = mapKey
					cLoadbalance := goLoadbalance.ToClang()
					if err := cLoadbalance.Update(&mapKey); err != nil {
						return fmt.Errorf("add loadbalance failed, %v, %s", mapKey, err)
					}

					event.endpointsAddressToMapKey[goEndpoint.Address] = mapKey
					event.endpointsCount[mapKey.Port]++
					mapKey.Index++
				}
			}
		}
	}

	return nil
}

func (event *ClientEvent) UpdateEndpoint() error {
	var (
		mapKey maps.GoMapKey
		goEndpoint maps.GoEndpoint
	)

	// Update map of endpoint
	for _, ep := range event.Endpoints {
		for _, sub := range ep.Subsets {
			for _, epPort := range sub.Ports {
				if !option.EnabledProtocolConfig(string(epPort.Protocol)) {
					continue
				}

				goEndpoint.Address.Protocol = ProtocolStrToC[epPort.Protocol]
				goEndpoint.Address.Port = nets.ConvertPortToLittleEndian(epPort.Port)

				for _, epAddr := range sub.Addresses {
					goEndpoint.Address.IPv4 = nets.ConvertIpToUint32(epAddr.IP)

					mapKey = event.endpointsAddressToMapKey[goEndpoint.Address]

					cEndpoint := goEndpoint.ToClang()
					if err := cEndpoint.Update(&mapKey); err != nil {
						event.DeleteEndpoint()
						return fmt.Errorf("update endpoint failed, %v, %s", mapKey, err)
					}
				}
			}
		}
	}

	return nil
}

func (event *ClientEvent) DeleteEndpoint() error {
	// FIXME: 没有收到apiserver删除endpoint的事件
	// TODO
	// 1. 使用 event.endpointsAddressToMapKey
	// 2. 更新 map_of_endpoint map_of_loadbalance
	//      找到最后一个条目
	//      覆盖要删除的条目
	//      删除最后一个条目
	// 3. 计数 event.endpointsCount--
	// 4. 删除 event.endpointsAddressToMapKey
	// 5. 删除 convert.Delete()
	return nil
}

func (event *ClientEvent) addCluster() error {
	var (
		mapKey maps.GoMapKey
		goCluster maps.GoCluster
	)

	if event.Service == nil {
		return nil
	}
	mapKey.NameID = convert.StrToNum(event.Key.name)

	// TODO
	//goCluster.Type = 0
	//goCluster.ConnectTimeout = 15

	for _, serPort := range event.Service.Spec.Ports {
		if !option.EnabledProtocolConfig(string(serPort.Protocol)) {
			continue
		}

		mapKey.Port = nets.ConvertPortToLittleEndian(serPort.TargetPort.IntVal)
		goCluster.LoadAssignment.MapKeyOfEndpoint = mapKey

		mapKey.Port = nets.ConvertPortToLittleEndian(serPort.Port)
		cCluster := goCluster.ToClang()
		if err := cCluster.Update(&mapKey); err != nil {
			event.DeleteCluster()
			return fmt.Errorf("add cluster failed, %v, %s", mapKey, err)
		}
		event.serviceCount[mapKey.Port] = 1
	}

	return nil
}

func (event *ClientEvent) UpdateCluster() error {
	return event.addCluster()
}

func (event *ClientEvent) DeleteCluster() error {
	// TODO
	// 1. 从apiserver收到删除service的事件
	// 2. 删除相关的所有map条目
	// 3. 重置计数 event.serviceCount = 0
	return nil
}

func (event *ClientEvent) addListener() error {
	var (
		goListener maps.GoListener
	)

	if event.Service == nil {
		return nil
	}
	goListener.MapKey.NameID = convert.StrToNum(event.Key.name)

	goListener.Type = C.LISTENER_TYPE_DYNAMIC
	goListener.State = C.LISTENER_STATE_ACTIVE

	for _, serPort := range event.Service.Spec.Ports {
		if !option.EnabledProtocolConfig(string(serPort.Protocol)) {
			continue
		}

		goListener.MapKey.Port = nets.ConvertPortToLittleEndian(serPort.Port)
		// TODO: goListener.Address.Protocol = ProtocolStrToC[serPort.Protocol]

		switch event.Service.Spec.Type {
		case apiCoreV1.ServiceTypeNodePort:
			goListener.Address.Port = nets.ConvertPortToLittleEndian(serPort.NodePort)

			for _, node := range nodesMap {
				for _, addr := range node.Status.Addresses {
					// TODO: addr.Type == apiCoreV1.NodeExternalIP
					if addr.Type != apiCoreV1.NodeInternalIP {
						continue
					}
					goListener.Address.IPv4 = nets.ConvertIpToUint32(addr.Address)

					cListener := goListener.ToClang()
					if err := cListener.Update(&goListener.Address); err != nil {
						event.DeleteListener()
						return fmt.Errorf("add listener failed, %v, %s", goListener.Address, err)
					}
				}
			}

			fallthrough
		case apiCoreV1.ServiceTypeClusterIP:
			// TODO: event.Service.Spec.ExternalIPs
			goListener.Address.IPv4 = nets.ConvertIpToUint32(event.Service.Spec.ClusterIP)
			goListener.Address.Port = nets.ConvertPortToLittleEndian(serPort.Port)

			cListener := goListener.ToClang()
			if err := cListener.Update(&goListener.Address); err != nil {
				event.DeleteListener()
				return fmt.Errorf("add listener failed, %v, %s", goListener.Address, err)
			}
		case apiCoreV1.ServiceTypeLoadBalancer:
			// TODO
		case apiCoreV1.ServiceTypeExternalName:
			// TODO
		default:
		}
	}

	return nil
}

func (event *ClientEvent) UpdateListener() error {
	return event.addListener()
}

func (event *ClientEvent) DeleteListener() error {
	// TODO
	// NodePort模式
	// 1. 从apiserver收到删除node的事件
	// 2. 删除nodeIP相关的map条目
	// ClusterIP模式
	// 1. 从apiserver收到删除service的事件
	// 2. 删除相关的所有map条目
	return nil
}
