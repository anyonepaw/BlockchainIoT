/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 3  * This program is free software; you can redistribute it and/or modify
 4  * it under the terms of the GNU General Public License version 2 as
 5  * published by the Free Software Foundation;
 6  *
 7  * This program is distributed in the hope that it will be useful,
 8  * but WITHOUT ANY WARRANTY; without even the implied warranty of
 9  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 10  * GNU General Public License for more details.
 11  *
 12  * You should have received a copy of the GNU General Public License
 13  * along with this program; if not, write to the Free Software
 14  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 15  *
 16  * Author: John Abraham <john.abraham@gatech.edu>
 17  http://code.nsnam.org/jabraham3/topo/rev/186744a085ed
 */

#include <cmath>
#include <iostream>
#include <sstream>


#include "ns3/random-variable-stream.h"

#include "ns3/point-to-point-helper.h"
#include "ns3/ptr.h"
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/log.h"
#include "ns3/point-to-point-ring.h"
#include "ns3/constant-position-mobility-model.h"

NS_LOG_COMPONENT_DEFINE("PointToPointRingHelper");

namespace ns3{



PointToPointRingHelper::PointToPointRingHelper(uint32_t num_nodes, PointToPointHelper p2pHelper, bool full_clique, bool random_clique) {
	m_ringContainer.Create(num_nodes);
	P2PConnectHelper(p2pHelper, full_clique, random_clique);
}

void PointToPointRingHelper::P2PConnectHelper(PointToPointHelper p2pHelper,
		bool full_clique, bool random_clique) {
	if (!(full_clique || random_clique)) {
		for (uint32_t i = 0; i < m_ringContainer.GetN() - 1; i++)
			m_nd.push_back(
					p2pHelper.Install(m_ringContainer.Get(i),
							m_ringContainer.Get(i + 1)));

		m_nd.push_back(
				p2pHelper.Install(m_ringContainer.Get(0),
						m_ringContainer.Get(m_ringContainer.GetN() - 1)));

	} else {
		for (uint32_t i = 0; i < m_ringContainer.GetN() - 1; i++) {
			for (uint32_t j = 0; j < m_ringContainer.GetN(); j++) {
				if (j == i)
					continue;
				uint32_t lowerbound = full_clique ? 1 : 0;
				UniformRandomVariable v;
				if (v.GetInteger(lowerbound, 1)) {
					m_nd.push_back(
							p2pHelper.Install(m_ringContainer.Get(i),
									m_ringContainer.Get(j)));

				} else {
					std::cout << "Not connecting" << std::endl;

				}

			} //For 2

		} //for 1

	}

}

Ptr<Node> PointToPointRingHelper::Get(uint32_t index) {
	NS_ASSERT(index < m_ringContainer.GetN());
	return m_ringContainer.Get(index);

}
uint32_t PointToPointRingHelper::GetN() {
	return m_ringContainer.GetN();

}

Ptr<Node> PointToPointRingHelper::GetFirst() {
	return m_ringContainer.Get(0);

}

Ptr<Node> PointToPointRingHelper::GetLast() {
	return m_ringContainer.Get(m_ringContainer.GetN() - 1);

}

void PointToPointRingHelper::InstallStack(InternetStackHelper stack) {
	stack.Install(m_ringContainer);

}

void PointToPointRingHelper::AssignIpv4Addresses(Ipv4AddressHelper ip) {
	for (uint32_t i = 0; i < m_nd.size(); i++) {
		m_interfaces.Add(ip.Assign(m_nd[i]));
		ip.NewNetwork();
	}
}

Ipv4Address
PointToPointRingHelper::GetIpv4Address (uint32_t i) const
{
  return m_interfaces.GetAddress (i);
}


void PointToPointRingHelper::BoundingBox(double ulx, double uly, double lrx,
		double lry) {
	double yDist;
	double xDist;
	double centerX, centerY, radiusX, radiusY;
	if (lrx > ulx) {
		xDist = lrx - ulx;

	} else {
		xDist = ulx - lrx;

	}
	if (lry > uly) {
		yDist = lry - uly;

	} else {
		yDist = uly - lry;

	}
	centerX = xDist / 2;
	centerY = yDist / 2;
	radiusX = centerX;
	radiusY = centerY;
	double angle = (2 * M_PI) / m_ringContainer.GetN();
	for (uint32_t l = 0; l < m_ringContainer.GetN(); l++) {
		Ptr <Node> n = m_ringContainer.Get(l);
		Ptr <ConstantPositionMobilityModel> loc = n->GetObject<ConstantPositionMobilityModel>();
		if (loc == 0) {
			loc = CreateObject<ConstantPositionMobilityModel>();
			n->AggregateObject(loc);

		}
		Vector vec(centerX + radiusX * cos(angle * l),
				centerY + radiusY * sin(angle * l), 0);
		loc->SetPosition(vec);

	}

}

} // namespace ns3

