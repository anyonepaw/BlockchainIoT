
/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: John Abraham <john.abraham@gatech.edu>
 */

#ifndef POINT_TO_POINT_RING_HELPER_H
#define POINT_TO_POINT_RING_HELPER_H

#include "ns3/point-to-point-helper.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ipv4-interface-container.h"
#include "internet-stack-helper.h"

#include <vector>

namespace ns3 {

class PointToPointRingHelper {
public:
	PointToPointRingHelper (uint32_t num_nodes,PointToPointHelper p2pHelper,bool full_clique = false,bool random_clique = false);
	~PointToPointRingHelper ()
	{
	}


	void BoundingBox(double ulx, double uly, double lrx, double lry);
	void InstallStack(InternetStackHelper stack);
	void AssignIpv4Addresses(Ipv4AddressHelper ip);
	Ipv4Address	GetIpv4Address (uint32_t i) const;
	Ptr<Node> Get(uint32_t index);
	uint32_t GetN();
	Ptr<Node> GetFirst();
	Ptr<Node> GetLast();

	private:
    uint32_t m_num_nodes;
	NodeContainer m_ringContainer;
    Ipv4InterfaceContainer m_interfaces;
	std::vector<NetDeviceContainer> m_nd;
	void P2PConnectHelper(PointToPointHelper p2pHelper,
			bool full_clique = false, bool random_clique = false);

};

} // namespace ns3
#endif

