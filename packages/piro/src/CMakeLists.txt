
#
# A) Package-specific configuration options
#

TRIBITS_CONFIGURE_FILE(${PACKAGE_NAME}_config.hpp)

#
# B) Define the header and source files (and directories)
#


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
SET(HEADERS ${HEADERS}
  ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}_config.hpp
  )

#
# B.1) utilities
#
APPEND_SET(HEADERS
  Piro_ValidPiroParameters.hpp
  Piro_Version.hpp
  Piro_InvertMassMatrixDecorator.hpp
  Piro_InvertMassMatrixDecorator_Def.hpp
  Piro_Provider.hpp
  Piro_ProviderBase.hpp
  Piro_ProviderHelpers.hpp
  Piro_SolutionObserverBase.hpp
  Piro_SolverFactory.hpp
  Piro_SolverFactory_Def.hpp
  Piro_StratimikosUtils.hpp
  Piro_ConfigDefs.hpp
  )
IF(Piro_ENABLE_Epetra)
APPEND_SET(HEADERS
  Piro_Epetra_MatrixFreeDecorator.hpp
  Piro_Epetra_InvertMassMatrixDecorator.hpp
  Piro_Epetra_SolverFactory.hpp
  )
ENDIF()
APPEND_SET(SOURCES
  Piro_ValidPiroParameters.cpp
  Piro_StratimikosUtils.cpp
  Piro_Version.cpp
  )
IF(Piro_ENABLE_Epetra)
APPEND_SET(SOURCES
  Piro_Epetra_MatrixFreeDecorator.cpp
  Piro_Epetra_InvertMassMatrixDecorator.cpp
  Piro_Epetra_SolverFactory.cpp
  )
ENDIF()
APPEND_SET(HEADERS
  Piro_MatrixFreeDecorator.hpp
  Piro_MatrixFreeDecorator_Def.hpp
  Piro_MatrixFreeLinearOp.hpp
  Piro_MatrixFreeLinearOp_Def.hpp
  Piro_ObserverBase.hpp
  )
#
# B.2) epetra files
#
# Optional NOX Dependency (which includes LOCA)
IF (Piro_ENABLE_NOX)
  APPEND_SET(HEADERS
    Piro_SteadyStateSolver.hpp
    Piro_SteadyStateSolver_Def.hpp
    Piro_NOXSolver.hpp
    Piro_NOXSolver_Def.hpp
    Piro_LOCASolver.hpp
    Piro_LOCASolver_Def.hpp
    Piro_LOCAAdaptiveSolver.hpp
    Piro_LOCAAdaptiveSolver_Def.hpp
    Piro_ObserverToLOCASaveDataStrategyAdapter.hpp
    Piro_VelocityVerletSolver.hpp
    Piro_VelocityVerletSolver_Def.hpp
    Piro_TrapezoidRuleSolver.hpp
    Piro_TrapezoidRuleSolver_Def.hpp
    Piro_TransientDecorator.hpp
  )
IF(Piro_ENABLE_Epetra)
  APPEND_SET(HEADERS
    Piro_Epetra_NOXSolver.hpp
    Piro_Epetra_LOCASolver.hpp
    Piro_Epetra_LOCAAdaptiveSolver.hpp
    Piro_Epetra_AdaptiveSolutionManager.hpp
    Piro_Epetra_VelocityVerletSolver.hpp
    Piro_Epetra_NewmarkSolver.hpp
    Piro_Epetra_TrapezoidRuleSolver.hpp
    Piro_Epetra_SensitivityOperator.hpp
  )
ENDIF()
  APPEND_SET(SOURCES
    Piro_NOXSolver.cpp
    Piro_LOCASolver.cpp
    Piro_LOCAAdaptiveSolver.cpp
    Piro_ObserverToLOCASaveDataStrategyAdapter.cpp
    )
IF(Piro_ENABLE_Epetra)
  APPEND_SET(SOURCES
    Piro_Epetra_NOXSolver.cpp
    Piro_Epetra_LOCASolver.cpp
    Piro_Epetra_LOCAAdaptiveSolver.cpp
    Piro_Epetra_AdaptiveSolutionManager.cpp
    Piro_Epetra_VelocityVerletSolver.cpp
    Piro_Epetra_NewmarkSolver.cpp
    Piro_Epetra_TrapezoidRuleSolver.cpp
    Piro_Epetra_SensitivityOperator.cpp
    )
ENDIF()
ENDIF()
# Optional Rythmos Dependency
IF (Piro_ENABLE_Rythmos)
  APPEND_SET(HEADERS
    Piro_RythmosSolver.hpp
    Piro_RythmosStepperFactory.hpp
    Piro_RythmosStepControlFactory.hpp
    Piro_RythmosSolver_Def.hpp
    Piro_ObserverToRythmosIntegrationObserverAdapter.hpp
    Piro_ObserverToRythmosIntegrationObserverAdapter_Def.hpp
    )
IF(Piro_ENABLE_Epetra)
  APPEND_SET(HEADERS
    Piro_Epetra_RythmosSolver.hpp
  )
  APPEND_SET(SOURCES Piro_Epetra_RythmosSolver.cpp)
ENDIF()
ENDIF()
IF (Piro_ENABLE_Tempus)
  APPEND_SET(HEADERS
    Piro_TempusSolver.hpp
    Piro_TempusSolver_Def.hpp 
    Piro_TransientSolver.hpp
    Piro_TransientSolver_Def.hpp 
    Piro_TempusStepperFactory.hpp
    Piro_TempusStepControlFactory.hpp
    Piro_ObserverToTempusIntegrationObserverAdapter.hpp 
    Piro_ObserverToTempusIntegrationObserverAdapter_Def.hpp) 
ENDIF()

IF (Piro_ENABLE_Rythmos AND Piro_ENABLE_NOX)
  APPEND_SET(HEADERS Piro_RythmosNOX_RowSumUpdater.hpp)
ENDIF()

# Optional StochasticGalerkin capability, depending upon Stokhos and NOX
IF (Piro_ENABLE_Stokhos AND Piro_ENABLE_NOX AND Piro_ENABLE_Epetra)
  APPEND_SET(HEADERS
    Piro_Epetra_StokhosNOXObserver.hpp
    Piro_Epetra_StokhosSolverFactory.hpp
    Piro_Epetra_StokhosSolver.hpp
    Piro_Epetra_StokhosMPSolver.hpp
    Piro_Epetra_NECoupledModelEvaluator.hpp
    )
  APPEND_SET(SOURCES
    Piro_Epetra_StokhosNOXObserver.cpp
    Piro_Epetra_StokhosSolverFactory.cpp
    Piro_Epetra_StokhosSolver.cpp
    Piro_Epetra_StokhosMPSolver.cpp
    Piro_Epetra_NECoupledModelEvaluator.cpp
    )
ENDIF()

# Add rol/adapters/thyra directories if Rol is enabled
IF (Piro_ENABLE_ROL)
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../rol/adapters/thyra/src/function)
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../rol/adapters/thyra/src/vector)
ENDIF()
#

#
# B.2) Analysis Tools
#

IF (Piro_ENABLE_TriKota)
  ADD_DEFINITIONS(${TRIKOTA_DAKOTA_DEFINITIONS})
ENDIF()

APPEND_SET(HEADERS
  Piro_PerformSolve.hpp
  Piro_PerformSolve_Def.hpp
  )
APPEND_SET(SOURCES Piro_PerformSolve.cpp)

IF(Piro_ENABLE_Epetra)
APPEND_SET(HEADERS Piro_Epetra_PerformSolve.hpp)
APPEND_SET(SOURCES Piro_Epetra_PerformSolve.cpp)
APPEND_SET(HEADERS Piro_Epetra_PerformAnalysis.hpp)
APPEND_SET(SOURCES Piro_Epetra_PerformAnalysis.cpp)
ENDIF()

APPEND_SET(HEADERS Piro_PerformAnalysis.hpp)
APPEND_SET(SOURCES Piro_PerformAnalysis.cpp)

IF (Piro_ENABLE_TriKota AND Piro_ENABLE_Stokhos AND Piro_ENABLE_NOX AND Piro_ENABLE_Epetra)
  APPEND_SET(HEADERS TriKota_MPDirectApplicInterface.hpp)
  APPEND_SET(SOURCES TriKota_MPDirectApplicInterface.cpp)
ENDIF()

#
# C) Define the targets for package's library(s)
#

TRIBITS_ADD_LIBRARY(
  piro
  HEADERS ${HEADERS}
  SOURCES ${SOURCES}
  )
