//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014, Lawrence Livermore National Security, LLC. Produced
// at the Lawrence Livermore National Laboratory. Written by Alfredo
// Gimenez (alfredo.gimenez@gmail.com). LLNL-CODE-663358. All rights
// reserved.
//
// This file is part of MemAxes. For details, see
// https://github.com/scalability-tools/MemAxes
//
// Please also read this link – Our Notice and GNU Lesser General Public
// License. This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License (as
// published by the Free Software Foundation) version 2.1 dated February
// 1999.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the IMPLIED WARRANTY OF
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the terms and
// conditions of the GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
// OUR NOTICE AND TERMS AND CONDITIONS OF THE GNU GENERAL PUBLIC LICENSE
// Our Preamble Notice
// A. This notice is required to be provided under our contract with the
// U.S. Department of Energy (DOE). This work was produced at the Lawrence
// Livermore National Laboratory under Contract No. DE-AC52-07NA27344 with
// the DOE.
// B. Neither the United States Government nor Lawrence Livermore National
// Security, LLC nor any of their employees, makes any warranty, express or
// implied, or assumes any liability or responsibility for the accuracy,
// completeness, or usefulness of any information, apparatus, product, or
// process disclosed, or represents that its use would not infringe
// privately-owned rights.
//////////////////////////////////////////////////////////////////////////////

#ifndef CLUSTERMETRICS_H
#define CLUSTERMETRICS_H

#include "dataobject.h"
#include "hwtopo.h"

class HWTopo;

enum METRIC_TYPE
{
    CORE_IMBALANCE = 0,
    L1_IMBALANCE,
    L2_IMBALANCE,
    L3_IMBALANCE,
    NUMA_IMBALANCE
};

class ClusterAggregate
{
public:
    virtual void createAggregateFromSamples(DataObject *d, ElemSet *s) = 0;
};

class HardwareClusterAggregate : public ClusterAggregate
{
public:
    HardwareClusterAggregate();
    virtual void createAggregateFromSamples(DataObject *d, ElemSet *s);

    qreal distance(HardwareClusterAggregate *other, METRIC_TYPE m);
    void initFrom(DataObject *d, HardwareClusterAggregate *hcm);
    void combineAggregate(DataObject *d, HardwareClusterAggregate *hcm);

    HWTopo *getTopo() {return topo;}
    void setTopo(HWTopo *t);

    qreal getMetric(METRIC_TYPE t);

    qreal getCoreImbalance();
    qreal getL1Imbalance();
    qreal getL2Imbalance();
    qreal getL3Imbalance();
    qreal getNUMAImbalance();

private:
    HWTopo *topo;

    std::vector<int> depthSamples;
    std::vector<qreal> depthAvgSamples;
    std::vector<qreal> depthMeans;
    std::vector<qreal> depthStddevs;
    std::vector<qreal> depthImbalances;
};

#endif
