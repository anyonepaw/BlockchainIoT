/*
 * examr.cc
 *
 *  Created on: Jan 24, 2019
 *      Author: lika
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/netanim-module.h"
#include "ns3/mobility-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Ring");

int main(int argc, char *argv[]) {

	uint32_t number_of_nodes = 5;

	CommandLine cmd;
	cmd.Parse(argc, argv);

	MobilityHelper mobility;
		Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
	positionAlloc->Add(Vector(15.0, 0.0, 0.0));
	positionAlloc->Add(Vector(30.0, 10.0, 0.0));
	positionAlloc->Add(Vector(25.0, 25.0, 0.0));
	positionAlloc->Add(Vector(5.0, 25.0, 0.0));
	positionAlloc->Add(Vector(0.0, 10.0, 0.0));


	NS_LOG_INFO("Build ring topology.");
	PointToPointHelper pointToPoint;
	PointToPointRingHelper ring(number_of_nodes, pointToPoint);


	mobility.SetPositionAllocator(positionAlloc);
		mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
		mobility.Install(ring.Get(0));
		mobility.Install(ring.Get(1));
		mobility.Install(ring.Get(2));
		mobility.Install(ring.Get(3));
		mobility.Install(ring.Get(4));

	NS_LOG_INFO("Install Internet stack on all nodes.");
	InternetStackHelper internet;
	ring.InstallStack(internet);

	NS_LOG_INFO("Assign IP Addresses.");
	ring.AssignIpv4Addresses(Ipv4AddressHelper("10.1.1.0", "255.255.255.0"));

	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	uint16_t port = 50000;

	OnOffHelper onOffHelper("ns3::TcpSocketFactory", Address());
	onOffHelper.SetAttribute("OnTime",
			StringValue("ns3::ConstantRandomVariable[Constant=1]"));
	onOffHelper.SetAttribute("OffTime",
			StringValue("ns3::ConstantRandomVariable[Constant=0]"));

	ApplicationContainer ringNodesApps;
	for (uint32_t i = 0; i < number_of_nodes - 1; i++) {
		AddressValue remoteAddress(
				InetSocketAddress(ring.GetIpv4Address(i), port));
		onOffHelper.SetAttribute("Remote", remoteAddress);
		ringNodesApps.Add(onOffHelper.Install(ring.Get(i + 1)));
	}
	AddressValue remoteAddress(InetSocketAddress(ring.GetIpv4Address(0), port));
	onOffHelper.SetAttribute("Remote", remoteAddress);
	ringNodesApps.Add(onOffHelper.Install(ring.Get(number_of_nodes - 1)));

	ringNodesApps.Start(Seconds(1.0));
	ringNodesApps.Stop(Seconds(10.0));

	AnimationInterface anim ("examr.xml");



	NS_LOG_INFO("Run Simulation.");
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO("Done.");

	return 0;
}

