/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * DDoS-attack
 *
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/random-variable-stream.h"
#include "limits.h"

// Network topology (default)
//
//        n2 n3 n4              .
//         \ | /                .
//          \|/                 .
//     n1--- n0---n5            .
//          /|\                 .
//         / | \                .
//        n8 n7 n6              .
//


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Attack");

int 
main (int argc, char *argv[])
{
  // Set up some default values for the simulation.
  Config::SetDefault ("ns3::OnOffApplication::PacketSize", UintegerValue (137));
  // ??? try and stick 15kb/s into the data rate
  Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue ("14kb/s"));
  // Default number of nodes in the star.  Overridable by command line argument.

  RngSeedManager::SetSeed(3);
  RngSeedManager::SetRun(7);


  Ptr<UniformRandomVariable> uv = CreateObject<UniformRandomVariable> ();
  uint32_t nSpokes = 13;


  CommandLine cmd;
  cmd.AddValue ("nSpokes", "Number of nodes to place in the star", nSpokes);
  cmd.Parse (argc, argv);

  NS_LOG_INFO ("Build star topology.");
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
  PointToPointStarHelper star (nSpokes, pointToPoint);

  NS_LOG_INFO ("Install Internet stack on all nodes.");
  InternetStackHelper internet;
  star.InstallStack (internet);

  NS_LOG_INFO ("Assign IP Addresses.");
  star.AssignIpv4Addresses (Ipv4AddressHelper ("10.1.1.0", "255.255.255.0"));

  NS_LOG_INFO ("Create applications.");
  // Create a packet sink on the star "hub" to receive packets.
  uint16_t port = 50000;
  Address hubLocalAddress (InetSocketAddress (Ipv4Address::GetAny (), port));
  PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", hubLocalAddress);
  ApplicationContainer hubApp = packetSinkHelper.Install (star.GetHub ());
  hubApp.Start (Seconds (1.0));
  hubApp.Stop (Seconds (100.0));


  // Create OnOff applications to send TCP to the hub, one on each spoke node.
  OnOffHelper onOffHelper ("ns3::TcpSocketFactory", Address ());
  onOffHelper.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  onOffHelper.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));

  //ddos
  BulkSendHelper bulkHelper ("ns3::TcpSocketFactory", Address ());
  bulkHelper.SetAttribute ("MaxBytes", UintegerValue (0));


  ApplicationContainer spokeOnOffApps;
  ApplicationContainer spokeBulkApps;
  ApplicationContainer spokeBulkApps1;

  for (uint32_t i = 0; i < star.SpokeCount (); ++i)
    {
      AddressValue remoteAddress (InetSocketAddress (star.GetHubIpv4Address (i), port));
      onOffHelper.SetAttribute ("Remote", remoteAddress);
      bulkHelper.SetAttribute ("Remote", remoteAddress);

      spokeOnOffApps.Add (onOffHelper.Install (star.GetSpokeNode (i)));
      spokeBulkApps.Add (bulkHelper.Install (star.GetSpokeNode (4)));
      spokeBulkApps1.Add (bulkHelper.Install (star.GetSpokeNode (9)));
    }

  spokeOnOffApps.Start (Seconds (1.0));
  spokeOnOffApps.Stop (Seconds (30.0));

  double start1 = 12;
  double stop1  = 15;

  spokeBulkApps.Start (Seconds (start1));
  spokeBulkApps.Stop (Seconds (stop1));

  double start2 = 25;
  double stop2  = 27;

  spokeBulkApps1.Start (Seconds (start2));
  spokeBulkApps1.Stop (Seconds (stop2));

  AnimationInterface anim ("my_example_1.xml");

  NS_LOG_INFO ("Enable static global routing.");
  // Turn on global static routing so we can actually be
  //routed across the star.
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  NS_LOG_INFO ("Enable pcap tracing.");

  // Do pcap tracing on all point-to-point devices on all nodes.
  pointToPoint.EnablePcapAll ("attack");

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Run ();
  Simulator::Destroy ();
  NS_LOG_INFO ("Done.");

  return 0;
}
