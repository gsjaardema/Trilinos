// @HEADER
// ****************************************************************************
//                Tempus: Copyright (2017) Sandia Corporation
//
// Distributed under BSD 3-clause license (See accompanying file Copyright.txt)
// ****************************************************************************
// @HEADER

#include "Teuchos_UnitTestHarness.hpp"
#include "Teuchos_XMLParameterListHelpers.hpp"
#include "Teuchos_TimeMonitor.hpp"
#include "Teuchos_DefaultComm.hpp"

#include "Thyra_VectorStdOps.hpp"

#include "Tempus_StepperFactory.hpp"
#include "Tempus_UnitTest_Utils.hpp"

#include "../TestModels/SinCosModel.hpp"
#include "../TestModels/VanDerPolModel.hpp"
#include "../TestUtils/Tempus_ConvergenceTestUtils.hpp"

#include <fstream>
#include <vector>

namespace Tempus_Unit_Test {

using Teuchos::RCP;
using Teuchos::rcp;
using Teuchos::rcp_const_cast;
using Teuchos::rcp_dynamic_cast;
using Teuchos::ParameterList;
using Teuchos::sublist;
using Teuchos::getParametersFromXmlFile;

using Tempus::StepperFactory;


// ************************************************************
// ************************************************************
TEUCHOS_UNIT_TEST(DIRK_2Stage2ndOrderLobattoIIIB, Default_Construction)
{
  testDIRKAccessorsFullConstruction("RK Implicit 2 Stage 2nd order Lobatto IIIB");
}


// ************************************************************
// ************************************************************
TEUCHOS_UNIT_TEST(DIRK_2Stage2ndOrderLobattoIIIB, StepperFactory_Construction)
{
  auto model = rcp(new Tempus_Test::SinCosModel<double>());
  testFactoryConstruction("RK Implicit 2 Stage 2nd order Lobatto IIIB", model);
}


// ************************************************************
// ************************************************************
TEUCHOS_UNIT_TEST(DIRK_2Stage2ndOrderLobattoIIIB, AppAction)
{
  testRKAppAction("RK Implicit 2 Stage 2nd order Lobatto IIIB", out, success);
}


} // namespace Tempus_Test
