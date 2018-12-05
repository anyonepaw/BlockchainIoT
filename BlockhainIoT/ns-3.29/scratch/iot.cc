/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 *
 *
 *       10.1.1.0
 * n0 -------------- n1
 *    point-to-point
 *
 *
 *
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("IoT-Simulator");

int 
main (int argc, char *argv[])
{
  NS_LOG_UNCOND ("");

  //Creating a wireless network
  //NodeContainer wifiStaNodes;
 // wifiStaNodes.Create(nWifi);
 // NodeContainer wifiApNode = p2pNodes.Get(0);

  Simulator::Run ();
  Simulator::Destroy ();

}
