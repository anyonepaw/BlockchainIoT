/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * DDoS-attack from lab
 *
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-layout-module.h"

using namespace ns3;
int
main (int argc, char *argv[])
{

Config::SetDefault ("ns3::OnOffApplication::PacketSize",
UintegerValue (137));
Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue
("14kb/s"));
uint32_t nSpokes = 8;
CommandLine cmd;
cmd.AddValue ("nSpokes", "Number of nodes to place in the star",
nSpokes);
cmd.Parse (argc, argv);
PointToPointHelper pointToPoint;
pointToPoint.SetDeviceAttribute ("DataRate", StringValue
("5Mbps"));
pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
PointToPointStarHelper star (nSpokes, pointToPoint);
InternetStackHelper internet;
star.InstallStack (internet);
star.AssignIpv4Addresses (Ipv4AddressHelper ("10.1.1.0",
"255.255.255.0"));
uint16_t port = 50000;
Address hubLocalAddress (InetSocketAddress (Ipv4Address::GetAny (),
port));
PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory",
hubLocalAddress);
ApplicationContainer hubApp = packetSinkHelper.Install (star.GetHub
());
hubApp.Start (Seconds (1.0));
hubApp.Stop (Seconds (100.0));
OnOffHelper onOffHelper ("ns3::TcpSocketFactory", Address ());
onOffHelper.SetAttribute ("OnTime", StringValue
("ns3::ConstantRandomVariable[Constant=1]"));
onOffHelper.SetAttribute ("OffTime", StringValue
("ns3::ConstantRandomVariable[Constant=0]"));


BulkSendHelper bulkHelper ("ns3::TcpSocketFactory", Address ());
bulkHelper.SetAttribute ("MaxBytes", UintegerValue (0));
ApplicationContainer spokeOnOffApps;
ApplicationContainer spokeBulkApps;
for (uint32_t i = 0; i < star.SpokeCount (); ++i)
{
AddressValue remoteAddress (InetSocketAddress
(star.GetHubIpv4Address (i), port));
onOffHelper.SetAttribute ("Remote", remoteAddress);
bulkHelper.SetAttribute ("Remote", remoteAddress);
spokeOnOffApps.Add (onOffHelper.Install (star.GetSpokeNode (i)));
spokeBulkApps.Add (bulkHelper.Install (star.GetSpokeNode (i)));
}
spokeOnOffApps.Start (Seconds (1.0));
spokeOnOffApps.Stop (Seconds (100.0));
spokeBulkApps.Start (Seconds (37.0));
spokeBulkApps.Stop (Seconds (44.0));
Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
pointToPoint.EnablePcapAll ("attack");
Simulator::Run ();
Simulator::Destroy ();
return 0;
}
