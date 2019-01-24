/*
 * route.cc
 *
 *  Created on: Jan 24, 2019
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

NS_LOG_COMPONENT_DEFINE("SimpleGlobalRoutingExample");

int main(int argc, char *argv[]) {
	// Users may find it convenient to turn on explicit debugging
	// for selected modules; the below lines suggest how to do this
#if 0
	LogComponentEnable ("SimpleGlobalRoutingExample", LOG_LEVEL_INFO);
#endif

	// Set up some default values for the simulation.  Use the
	Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(210));
	Config::SetDefault("ns3::OnOffApplication::DataRate",
			StringValue("448kb/s"));

	//DefaultValue::Bind ("DropTailQueue::m_maxPackets", 30);

	// Allow the user to override any of the defaults and the above
	// DefaultValue::Bind ()s at run-time, via command-line arguments
	CommandLine cmd;
	bool enableFlowMonitor = false;
	cmd.AddValue("EnableMonitor", "Enable Flow Monitor", enableFlowMonitor);
	cmd.Parse(argc, argv);

	// Here, we will explicitly create four nodes.  In more sophisticated
	// topologies, we could configure a node factory.
	NS_LOG_INFO("Create nodes.");
	NodeContainer c;
	c.Create(4);
	NodeContainer n0n2 = NodeContainer(c.Get(0), c.Get(1));
	NodeContainer n1n2 = NodeContainer(c.Get(1), c.Get(2));
	NodeContainer n2n3 = NodeContainer(c.Get(2), c.Get(3));

	InternetStackHelper internet;
	internet.Install(c);

	// We create the channels first without any IP addressing information
	NS_LOG_INFO("Create channels.");
	PointToPointHelper p2p;
	p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p.SetChannelAttribute("Delay", StringValue("2ms"));
	NetDeviceContainer d0d2 = p2p.Install(n0n2);
	NetDeviceContainer d1d2 = p2p.Install(n1n2);
	NetDeviceContainer d2d3 = p2p.Install(n2n3);

	// Later, we add IP addresses.
	NS_LOG_INFO("Assign IP Addresses.");
	Ipv4AddressHelper ipv4;
	ipv4.SetBase("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer i0i2 = ipv4.Assign(d0d2);

	Ipv4InterfaceContainer i1i2 = ipv4.Assign(d1d2);
	Ipv4InterfaceContainer i2i3 = ipv4.Assign(d2d3);

	// Create router nodes, initialize routing database and set up the routing
	// tables in the nodes.
	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	// Create the OnOff application to send UDP datagrams of size
	// 210 bytes at a rate of 448 Kb/s
	NS_LOG_INFO("Create Applications.");
	uint16_t port = 9;   // Discard port (RFC 863)
	OnOffHelper onoff("ns3::UdpSocketFactory",
			Address(InetSocketAddress(i1i2.GetAddress(0), port)));
	onoff.SetConstantRate(DataRate("288kb/s"));
	ApplicationContainer apps = onoff.Install(c.Get(0));
	apps.Start(Seconds(1.0));
	apps.Stop(Seconds(8.0));

	// Create a packet sink to receive these packets
	PacketSinkHelper sink("ns3::UdpSocketFactory",
			Address(InetSocketAddress(Ipv4Address::GetAny(), port)));
	apps = sink.Install(c.Get(1));
	apps.Start(Seconds(1.1));
	apps.Stop(Seconds(8.0));

	BulkSendHelper source("ns3::TcpSocketFactory",
			InetSocketAddress(i2i3.GetAddress(0), port));
	// Set the amount of data to send in bytes.  Zero is unlimited.
	source.SetAttribute("MaxBytes", UintegerValue(1000));
	ApplicationContainer sourceApps = source.Install(c.Get(2));
	sourceApps.Start(Seconds(8.0));
	sourceApps.Stop(Seconds(15.0));

	//
	// Create a PacketSinkApplication and install it on node 1
	//
	PacketSinkHelper sink2("ns3::TcpSocketFactory",
			InetSocketAddress(Ipv4Address::GetAny(), port));
	ApplicationContainer sinkApps = sink2.Install(c.Get(3));
	sinkApps.Start(Seconds(8.0));
	sinkApps.Stop(Seconds(15.0));

	// Flow Monitor
	FlowMonitorHelper flowmonHelper;
	if (enableFlowMonitor) {
		flowmonHelper.InstallAll();
	}

	NS_LOG_INFO("Run Simulation.");
	Simulator::Stop(Seconds(30));
	Simulator::Run();
	NS_LOG_INFO("Done.");

	Simulator::Destroy();
	return 0;
}

