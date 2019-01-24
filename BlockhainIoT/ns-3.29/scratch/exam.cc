/*
 * exam.cc
 *
 *  Created on: Jan 23, 2019
 *      Author: lika
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/ipv4-global-routing-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("ring");

int main(int argc, char *argv[]) {

	Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(210));
	Config::SetDefault("ns3::OnOffApplication::DataRate",
			StringValue("448kb/s"));

	CommandLine cmd;
	bool enableFlowMonitor = false;
	cmd.AddValue("EnableMonitor", "Enable Flow Monitor", enableFlowMonitor);
	cmd.Parse(argc, argv);

	NS_LOG_INFO("Create nodes.");
	NodeContainer c;
	c.Create(5);
	NodeContainer n0n1 = NodeContainer(c.Get(0), c.Get(1));
	NodeContainer n1n2 = NodeContainer(c.Get(1), c.Get(2));
	NodeContainer n2n3 = NodeContainer(c.Get(2), c.Get(3));
	NodeContainer n3n4 = NodeContainer(c.Get(3), c.Get(4));
	NodeContainer n4n0 = NodeContainer(c.Get(4), c.Get(0));

	InternetStackHelper internet;
	internet.Install(c);

	// We create the channels first without any IP addressing information
	NS_LOG_INFO("Create channels.");
	PointToPointHelper p2p;
	p2p.SetDeviceAttribute("DataRate", StringValue("500Kbps"));
	//p2p.SetChannelAttribute("Delay", StringValue("2ms"));
	NetDeviceContainer d0d1 = p2p.Install(n0n1);
	NetDeviceContainer d1d2 = p2p.Install(n1n2);
	NetDeviceContainer d2d3 = p2p.Install(n2n3);
	NetDeviceContainer d3d4 = p2p.Install(n3n4);
	NetDeviceContainer d4d0 = p2p.Install(n4n0);

	// Later, we add IP addresses.
	NS_LOG_INFO("Assign IP Addresses.");
	Ipv4AddressHelper ipv4;
	ipv4.SetBase("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer i0i1 = ipv4.Assign(d0d1);
	Ipv4InterfaceContainer i1i2 = ipv4.Assign(d1d2);
	Ipv4InterfaceContainer i2i3 = ipv4.Assign(d2d3);
	Ipv4InterfaceContainer i3i4 = ipv4.Assign(d3d4);
	Ipv4InterfaceContainer i4i0 = ipv4.Assign(d4d0);
	// Create router nodes, initialize routing database and set up the routing
	// tables in the nodes.
	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	NS_LOG_INFO("Create Applications.");
	uint16_t port = 9;   // Discard port (RFC 863)
	OnOffHelper onoff("ns3::TcpSocketFactory",
			Address(InetSocketAddress(i3i4.GetAddress(0), port)));
	onoff.SetConstantRate(DataRate("448kb/s"));
	ApplicationContainer apps = onoff.Install(c.Get(1));
	apps.Start(Seconds(1.0));
	apps.Stop(Seconds(10.0));



	/*
	 // Create a packet sink to receive these packets
	 PacketSinkHelper sink("ns3::UdpSocketFactory",
	 Address(InetSocketAddress(Ipv4Address::GetAny(), port)));
	 apps = sink.Install(c.Get(3));
	 apps.Start(Seconds(1.0));
	 apps.Stop(Seconds(10.0));
	 */
	// Flow Monitor
	FlowMonitorHelper flowmonHelper;
	if (enableFlowMonitor) {
		flowmonHelper.InstallAll();
	}

	//ddos
	BulkSendHelper bulkHelper("ns3::TcpSocketFactory", Address());
	bulkHelper.SetAttribute("MaxBytes", UintegerValue(0));
	ApplicationContainer spokeBulkApps;
	spokeBulkApps.Add(bulkHelper.Install(c.Get(4)));
	AddressValue remoteAddress(InetSocketAddress(i4i0.GetAddress(1), 9));
	bulkHelper.SetAttribute("Remote", remoteAddress);

	spokeBulkApps.Start(Seconds(4));
	spokeBulkApps.Stop(Seconds(15));


	PacketSinkHelper sink("ns3::TcpSocketFactory",
			InetSocketAddress(Ipv4Address::GetAny(), port));
	ApplicationContainer sinkApps = sink.Install(c.Get(0));
	sinkApps.Start(Seconds(4.0));
	sinkApps.Stop(Seconds(15.0));


	NS_LOG_INFO("Run Simulation.");
	Simulator::Stop(Seconds(30));
	Simulator::Run();
	NS_LOG_INFO("Done.");

	Simulator::Destroy();
	return 0;
}
