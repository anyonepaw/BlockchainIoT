/*
 * bulk.cc
 *
 *  Created on: Jan 24, 2019
 *      Author: lika
 */

// Network topology
//
//       n0 ----------- n1
//            500 Kbps
//             5 ms
//
// - Flow from n0 to n1 using BulkSendApplication.
// - Tracing of queues and packet receptions to file "tcp-bulk-send.tr"
//   and pcap tracing available when tracing is turned on.
#include <string>
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/network-module.h"
#include "ns3/packet-sink.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("TcpBulkSendExample");

int main(int argc, char *argv[]) {

	bool tracing = false;
	uint32_t maxBytes = 0;

	//
	// Allow the user to override any of the defaults at
	// run-time, via command-line arguments
	//
	CommandLine cmd;
	cmd.AddValue("tracing", "Flag to enable/disable tracing", tracing);
	cmd.AddValue("maxBytes", "Total number of bytes for application to send",
			maxBytes);
	cmd.Parse(argc, argv);

	//
	// Explicitly create the nodes required by the topology (shown above).
	//
	NS_LOG_INFO("Create nodes.");
	NodeContainer nodes;
	nodes.Create(2);
	NodeContainer c;
	c.Create(1);

	NS_LOG_INFO("Create channels.");

	//
	// Explicitly create the point-to-point link required by the topology (shown above).
	//
	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute("DataRate", StringValue("500Kbps"));
	pointToPoint.SetChannelAttribute("Delay", StringValue("5ms"));

	NetDeviceContainer devices = pointToPoint.Install(nodes);
	NetDeviceContainer d1d2 = pointToPoint.Install(nodes.Get(1), c.Get(0));
	//NetDeviceContainer d2d3 = pointToPoint.Install(nodes.Get(1),c .Get(0));



	//
	// Install the internet stack on the nodes
	//
	InternetStackHelper internet;
	internet.Install(nodes);
	internet.Install(c);

	//
	// We've got the "hardware" in place.  Now we need to add IP addresses.
	//
	NS_LOG_INFO("Assign IP Addresses.");
	Ipv4AddressHelper ipv4;
	ipv4.SetBase("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer i = ipv4.Assign(devices);
	Ipv4InterfaceContainer i2 = ipv4.Assign(d1d2);
	//Ipv4InterfaceContainer i3 = ipv4.Assign(d2d3);

	NS_LOG_INFO("Create Applications.");

	//
	// Create a BulkSendApplication and install it on node 0
	//
	uint16_t port = 9;  // well-known echo port number

	BulkSendHelper source("ns3::TcpSocketFactory",
			InetSocketAddress(i.GetAddress(0), port));
	// Set the amount of data to send in bytes.  Zero is unlimited.
	source.SetAttribute("MaxBytes", UintegerValue(500));
	ApplicationContainer sourceApps = source.Install(c.Get(0));
	sourceApps.Start(Seconds(0.0));
	sourceApps.Stop(Seconds(10.0));

	//
	// Create a PacketSinkApplication and install it on node 1
	//
	PacketSinkHelper sink("ns3::TcpSocketFactory",
			InetSocketAddress(Ipv4Address::GetAny(), port));
	ApplicationContainer sinkApps = sink.Install(nodes.Get(0));
	sinkApps.Start(Seconds(0.0));
	sinkApps.Stop(Seconds(10.0));

	//
	// Set up tracing if enabled
	//
	if (tracing) {
		AsciiTraceHelper ascii;
		pointToPoint.EnableAsciiAll(ascii.CreateFileStream("tcp-bulk-send.tr"));
		pointToPoint.EnablePcapAll("tcp-bulk-send", false);
	}

	//
	// Now, do the actual simulation.
	//
	NS_LOG_INFO("Run Simulation.");
	Simulator::Stop(Seconds(10.0));
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO("Done.");

	Ptr<PacketSink> sink1 = DynamicCast<PacketSink>(sinkApps.Get(0));
	std::cout << "Total Bytes Received: " << sink1->GetTotalRx() << std::endl;
}

