/*
 * ring.cc
 *
 *  Created on: Dec 13, 2018
 *      Author: lika
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-layout-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Ring");

int main(int argc, char *argv[]) {

	// Default number of nodes in the star.
	//Overridable by command line argument.
	uint32_t nSpokes = 10;
	CommandLine cmd;
	cmd.AddValue("nSpokes", "Number of nodes to place in the star", nSpokes);
	cmd.Parse(argc, argv);

	NS_LOG_INFO("Build ring topology.");
	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));
	PointToPointRingHelper ring(nSpokes, pointToPoint);

	NS_LOG_INFO("Install internet stack on all nodes.");
	InternetStackHelper internet;
	ring.InstallStack(internet);

	NS_LOG_INFO("Assign IP Addresses.");
	ring.AssignIpv4Addresses(Ipv4AddressHelper("10.1.1.0", "255.255.255.0"));

	//Another node with a p2p connection to the ring
	//NodeContainer p2pNodes;
	// p2pNodes.Add(ring.GetSpokeNode(nSpokes-1));
	// p2pNodes.Create(1);
	// internet.Install(p2pNodes.Get(1));
	// NetDeviceContainer p2pDevices = pointToPoint.Install(p2pNodes);


	//address.Assign(p2pDevices);

	NS_LOG_INFO("Create applications.");

	//------TCP------------//
	//
	// Create a packet sink on the star "hub" to receive packets.
	//
	uint16_t port = 50000;
	Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
	ring.AssignIpv4Addresses(address);

	//Address hubLocalAddress(InetSocketAddress(Ipv4Address::GetAny(), port));
    //PacketSinkHelper packetSinkHelper("ns3::TcpSocketFactory", hubLocalAddress);
	//ApplicationContainer hubApp = packetSinkHelper.Install(star.GetHub());
	//hubApp.Start(Seconds(1.0));
	//hubApp.Stop(Seconds(10.0));

	//
	// Create OnOff applications to send TCP to the hub, one on each spoke node.
	//
	OnOffHelper onOffHelper("ns3::TcpSocketFactory", Address());
	onOffHelper.SetAttribute("OnTime",
			StringValue("ns3::ConstantRandomVariable[Constant=1]"));
	onOffHelper.SetAttribute("OffTime",
			StringValue("ns3::ConstantRandomVariable[Constant=0]"));

	//ApplicationContainer spokeApps;

	//for (uint32_t i = 0; i < star.SpokeCount(); ++i) {
	//	AddressValue remoteAddress(
	//			InetSocketAddress(star.GetHubIpv4Address(i), port));
	//	onOffHelper.SetAttribute("Remote", remoteAddress);
	//	spokeApps.Add(onOffHelper.Install(star.GetSpokeNode(i)));
	//}
	//spokeApps.Start(Seconds(1.0));
	//spokeApps.Stop(Seconds(10.0));

	ApplicationContainer ringNodesApps;
	for (uint32_t i = 0; i < ring.GetN(); ++i) {
			AddressValue remoteAddress(
				InetSocketAddress(star.GetHubIpv4Address(i), port));
		//	onOffHelper.SetAttribute("Remote", remoteAddress);
		//	spokeApps.Add(onOffHelper.Install(star.GetSpokeNode(i)));
		//}
		//spokeApps.Start(Seconds(1.0));
		//spokeApps.Stop(Seconds(10.0));

	//AddressValue remoteAddress(
	//		InetSocketAddress(star.GetSpokeIpv4Address(0), port));
	//onOffHelper.SetAttribute("Remote", remoteAddress);
	//ApplicationContainer p2pApp;
	//p2pApp = onOffHelper.Install(p2pNodes.Get(1));
	//p2pApp.Start(Seconds(1.0));
	//p2pApp.Stop(Seconds(10.0));

	NS_LOG_INFO("Enable static global routing.");
	//
	// Turn on global static routing so we can actually be routed across the star.
	//
	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	NS_LOG_INFO("Enable pcap tracing.");
	//
	// Do pcap tracing on all point-to-point devices on all nodes.
	//
	//pointToPoint.EnablePcapAll("star");

	NS_LOG_INFO("Run Simulation.");
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO("Done.");

	return 0;
}

}
