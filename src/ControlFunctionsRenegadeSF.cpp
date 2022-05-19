#include "ControlFunctionsRenegadeSF.h"

// -------------------------------------------------------------
// CONFIRM All DEFINES MATCH DEVICE DEFINITIONS
// valveArray position defines for pointers
#define HiPress_ArrayPointer 0
#define HiPressVent_ArrayPointer 1
#define LoxMV_ArrayPointer 2
#define FuelMV_ArrayPointer 3
#define LoxVent_ArrayPointer 4
#define LoxDomeReg_ArrayPointer 5
#define LoxDomeRegVent_ArrayPointer 6
#define FuelVent_ArrayPointer 7
#define FuelDomeReg_ArrayPointer 8
#define FuelDomeRegVent_ArrayPointer 9

// pyroArray position defines for pointers
#define EngineIgniter0_ArrayPointer 0
#define EngineIgniter1_ArrayPointer 1

// autosequenceArray position defines for pointers
#define IgnitionAutoSequence 0

// sensorArray position defines for pointers
#define ThrustMountLoadCell1pos_ArrayPointer 0
#define ThrustMountLoadCell1neg_ArrayPointer 1
#define ThrustMountLoadCell2pos_ArrayPointer 2
#define ThrustMountLoadCell2neg_ArrayPointer 3
#define ThrustMountLoadCell3pos_ArrayPointer 4
#define ThrustMountLoadCell3neg_ArrayPointer 5
#define ChamberPT2_ArrayPointer 6
#define ChamberPT1_ArrayPointer 7
#define FuelInletPropSidePT_ArrayPointer 8
#define FuelInjectorPT_ArrayPointer 9
#define LoxInletPropSidePT_ArrayPointer 10
#define MVPneumaticsPT_ArrayPointer 11
#define DomeRegFuelPT_ArrayPointer 12
#define DomeRegLoxPT_ArrayPointer 13
#define FuelTankPT_ArrayPointer 14
#define LoxTankPT_ArrayPointer 15
#define HiPressFuelPT_ArrayPointer 16
#define HiPressLoxPT_ArrayPointer 17
#define MCUtempNode2_ArrayPointer 18
#define MCUtempNode3_ArrayPointer 19

// actuator position defines for pointers
#define Engine1TVC_Y_ArrayPointer 0
#define Engine1TVC_Z_ArrayPointer 2


// -------------------------------------------------------------

void startupStateCheck(const State& currentState, Command& currentCommand)
{
    switch (currentState)
    {
    case State::passive:
        currentCommand = command_passive;
        break;
    case State::test:
        currentCommand = command_test;
        break;
    case State::HiPressArm:
        currentCommand = command_HiPressArm;
        break;
    case State::HiPressPressurized:
        currentCommand = command_HiPressPressurized;
        break;
    case State::TankPressArm:
        currentCommand = command_TankPressArm;
        break;
    case State::TankPressPressurized:
        currentCommand = commend_TankPressPressurized;
        break;
    case State::fireArmed:
        currentCommand = command_fireArm;
        break;
    case State::fire: // if we powercycle mid fire, we just vent (maybe shouldn't always be true with multinode systems)
        currentCommand = command_abort;
        break;
    case State::abort:
        currentCommand = command_abort;
        break;
    case State::vent:
        currentCommand = command_vent;
        break;
    default:
        break;
    }
}

/* void haltFlagCheck(bool & haltFlag, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray)
{
    if(haltFlag)
    {
        valveArray.at(8)->setState(ValveState::CloseCommanded);     // Renegade SF Stand MV
        valveArray.at(9)->setState(ValveState::CloseCommanded);     // Renegade SF Stand MV
        pyroArray.at(0)->setState(PyroState::OffCommanded);         // Renegade SF Igniter1
        pyroArray.at(1)->setState(PyroState::OffCommanded);         // Renegade SF Igniter2
    }
    

} */


void vehicleStateMachine(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, bool & haltFlag)
{
    switch (currentCommand)
    {
        case command_debug:
            currentState = State::debug;
            break;
        case command_passive:
            valveArray.at(HiPress_ArrayPointer)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(HiPressVent_ArrayPointer)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(LoxMV_ArrayPointer)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(FuelMV_ArrayPointer)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(LoxVent_ArrayPointer)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(LoxDomeReg_ArrayPointer)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(LoxDomeRegVent_ArrayPointer)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(FuelVent_ArrayPointer)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(FuelDomeReg_ArrayPointer)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(FuelDomeRegVent_ArrayPointer)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter2
            sensorArray.at(0)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1pos
            sensorArray.at(1)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1neg
            sensorArray.at(2)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2pos
            sensorArray.at(3)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2neg
            sensorArray.at(4)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3pos
            sensorArray.at(5)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3neg
            sensorArray.at(6)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT2
            sensorArray.at(7)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT1
            sensorArray.at(8)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInletPropSidePT
            sensorArray.at(9)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInjectorPT
            sensorArray.at(10)->setState(SensorState::Medium);        // Renegade SF Stand - LoxInletPropSidePT
            sensorArray.at(11)->setState(SensorState::Medium);        // Renegade SF Stand - MVPneumaticsPT
            sensorArray.at(12)->setState(SensorState::Medium);        // Renegade SF Stand - DomeRegFuelPT
            sensorArray.at(13)->setState(SensorState::Medium);        // Renegade SF Stand - DomeRegLoxPT
            sensorArray.at(14)->setState(SensorState::Medium);        // Renegade SF Stand - FuelTankPT
            sensorArray.at(15)->setState(SensorState::Medium);        // Renegade SF Stand - LoxTankPT
            sensorArray.at(16)->setState(SensorState::Medium);        // Renegade SF Stand - HiPressFuelPT
            sensorArray.at(17)->setState(SensorState::Medium);        // Renegade SF Stand - HiPressLoxPT
            sensorArray.at(18)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode2
            sensorArray.at(19)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode3
            currentState = State::passive;
            haltFlag = false;
            break;
        case command_test:
            if(currentState == State::passive)
            {
            currentState = State::test;
            }
            break;
        case command_EnterOffNominal:
            priorState = currentState; //for remembering the state the system was in when entering Off Nominal
            currentState = State::offNominal;
            break;            
        case command_ExitOffNominal:
            if(currentState == State::offNominal)
            {
            currentState = priorState;              //IS THIS STILL TRUE???? - Beware, this currently doesn't function fully as desired. Will leave ValveEnables all on and not actually enter the prior command
            }
            break;
        case command_abort:
            haltFlag = true;
            currentState = State::abort;
            autoSequenceArray.at(0)->setState(AutoSequenceState::Hold);     // Renegade SF Stand
            break;
        case command_vent:
            valveArray.at(0)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(1)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(2)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(3)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(4)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(5)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(6)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(7)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(8)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(9)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter2            
            autoSequenceArray.at(0)->setState(AutoSequenceState::Hold);  // Renegade
            sensorArray.at(0)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1pos
            sensorArray.at(1)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1neg
            sensorArray.at(2)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2pos
            sensorArray.at(3)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2neg
            sensorArray.at(4)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3pos
            sensorArray.at(5)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3neg
            sensorArray.at(6)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT2
            sensorArray.at(7)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT1
            sensorArray.at(8)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInletPropSidePT
            sensorArray.at(9)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInjectorPT
            sensorArray.at(10)->setState(SensorState::Medium);        // Renegade SF Stand - LoxInletPropSidePT
            sensorArray.at(11)->setState(SensorState::Medium);        // Renegade SF Stand - MVPneumaticsPT
            sensorArray.at(12)->setState(SensorState::Medium);        // Renegade SF Stand - DomeRegFuelPT
            sensorArray.at(13)->setState(SensorState::Medium);        // Renegade SF Stand - DomeRegLoxPT
            sensorArray.at(14)->setState(SensorState::Fast);        // Renegade SF Stand - FuelTankPT
            sensorArray.at(15)->setState(SensorState::Fast);        // Renegade SF Stand - LoxTankPT
            sensorArray.at(16)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressFuelPT
            sensorArray.at(17)->setState(SensorState::Medium);        // Renegade SF Stand - HiPressLoxPT
            sensorArray.at(18)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode2
            sensorArray.at(19)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode3
            currentState = State::vent;
            break;
// Fire Sequence commands will only be executed from the proper state
        case command_HiPressArm:
            if(currentState == State::passive)
            {
            valveArray.at(0)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(1)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(2)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(3)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(4)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(5)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(6)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(7)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(8)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(9)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter2            
            autoSequenceArray.at(0)->setState(AutoSequenceState::Standby);  // Renegade SF Stand
            sensorArray.at(0)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1pos
            sensorArray.at(1)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1neg
            sensorArray.at(2)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2pos
            sensorArray.at(3)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2neg
            sensorArray.at(4)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3pos
            sensorArray.at(5)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3neg
            sensorArray.at(6)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT2
            sensorArray.at(7)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT1
            sensorArray.at(8)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInletPropSidePT
            sensorArray.at(9)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInjectorPT
            sensorArray.at(10)->setState(SensorState::Medium);        // Renegade SF Stand - LoxInletPropSidePT
            sensorArray.at(11)->setState(SensorState::Medium);        // Renegade SF Stand - MVPneumaticsPT
            sensorArray.at(12)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegFuelPT
            sensorArray.at(13)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegLoxPT
            sensorArray.at(14)->setState(SensorState::Medium);        // Renegade SF Stand - FuelTankPT
            sensorArray.at(15)->setState(SensorState::Medium);        // Renegade SF Stand - LoxTankPT
            sensorArray.at(16)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressFuelPT
            sensorArray.at(17)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressLoxPT
            sensorArray.at(18)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode2
            sensorArray.at(19)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode3
            currentState = State::HiPressArm;
            }
            break;
        case command_HiPressPressurized:
            if(currentState == State::HiPressArm || currentState == State::TankPressArm) //added second conditional to allow entry backwards in a "disarm" state change
            {
            valveArray.at(0)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(1)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(2)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(3)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(4)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(5)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(6)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(7)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(8)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(9)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter2            
            autoSequenceArray.at(0)->setState(AutoSequenceState::Standby);  // Renegade SF Stand
            sensorArray.at(0)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1pos
            sensorArray.at(1)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1neg
            sensorArray.at(2)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2pos
            sensorArray.at(3)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2neg
            sensorArray.at(4)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3pos
            sensorArray.at(5)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3neg
            sensorArray.at(6)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT2
            sensorArray.at(7)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT1
            sensorArray.at(8)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInletPropSidePT
            sensorArray.at(9)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInjectorPT
            sensorArray.at(10)->setState(SensorState::Medium);        // Renegade SF Stand - LoxInletPropSidePT
            sensorArray.at(11)->setState(SensorState::Medium);        // Renegade SF Stand - MVPneumaticsPT
            sensorArray.at(12)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegFuelPT
            sensorArray.at(13)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegLoxPT
            sensorArray.at(14)->setState(SensorState::Medium);        // Renegade SF Stand - FuelTankPT
            sensorArray.at(15)->setState(SensorState::Medium);        // Renegade SF Stand - LoxTankPT
            sensorArray.at(16)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressFuelPT
            sensorArray.at(17)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressLoxPT
            sensorArray.at(18)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode2
            sensorArray.at(19)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode3
            currentState = State::HiPressPressurized;
            }
            break;
        case command_TankPressArm:
            if(currentState == State::HiPressPressurized)
            {
            valveArray.at(0)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(1)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(2)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(3)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(4)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(5)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(6)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(7)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(8)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(9)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter2            
            autoSequenceArray.at(0)->setState(AutoSequenceState::Standby);  // Renegade SF Stand
            sensorArray.at(0)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1pos
            sensorArray.at(1)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1neg
            sensorArray.at(2)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2pos
            sensorArray.at(3)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2neg
            sensorArray.at(4)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3pos
            sensorArray.at(5)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3neg
            sensorArray.at(6)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT2
            sensorArray.at(7)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT1
            sensorArray.at(8)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInletPropSidePT
            sensorArray.at(9)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInjectorPT
            sensorArray.at(10)->setState(SensorState::Medium);        // Renegade SF Stand - LoxInletPropSidePT
            sensorArray.at(11)->setState(SensorState::Medium);        // Renegade SF Stand - MVPneumaticsPT
            sensorArray.at(12)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegFuelPT
            sensorArray.at(13)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegLoxPT
            sensorArray.at(14)->setState(SensorState::Fast);        // Renegade SF Stand - FuelTankPT
            sensorArray.at(15)->setState(SensorState::Fast);        // Renegade SF Stand - LoxTankPT
            sensorArray.at(16)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressFuelPT
            sensorArray.at(17)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressLoxPT
            sensorArray.at(18)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode2
            sensorArray.at(19)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode3
            currentState = State::TankPressArm;
            }
            break;
        case commend_TankPressPressurized:
            if(currentState == State::TankPressArm)
            {
            valveArray.at(0)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(1)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(2)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(3)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(4)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(5)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(6)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(7)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(8)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(9)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter2            
            autoSequenceArray.at(0)->setState(AutoSequenceState::Standby);  // Renegade SF Stand
            sensorArray.at(0)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1pos
            sensorArray.at(1)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell1neg
            sensorArray.at(2)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2pos
            sensorArray.at(3)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell2neg
            sensorArray.at(4)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3pos
            sensorArray.at(5)->setState(SensorState::Medium);         // Renegade SF Stand - ThrustMountLoadCell3neg
            sensorArray.at(6)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT2
            sensorArray.at(7)->setState(SensorState::Medium);         // Renegade SF Stand - ChamberPT1
            sensorArray.at(8)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInletPropSidePT
            sensorArray.at(9)->setState(SensorState::Medium);         // Renegade SF Stand - FuelInjectorPT
            sensorArray.at(10)->setState(SensorState::Medium);        // Renegade SF Stand - LoxInletPropSidePT
            sensorArray.at(11)->setState(SensorState::Medium);        // Renegade SF Stand - MVPneumaticsPT
            sensorArray.at(12)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegFuelPT
            sensorArray.at(13)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegLoxPT
            sensorArray.at(14)->setState(SensorState::Fast);        // Renegade SF Stand - FuelTankPT
            sensorArray.at(15)->setState(SensorState::Fast);        // Renegade SF Stand - LoxTankPT
            sensorArray.at(16)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressFuelPT
            sensorArray.at(17)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressLoxPT
            sensorArray.at(18)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode2
            sensorArray.at(19)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode3
            currentState = State::TankPressPressurized;
            }
            break;
        case command_fireArm:
            if(currentState == State::TankPressPressurized)
            {
            valveArray.at(0)->setState(ValveState::CloseCommanded);          // Renegade SF Stand
            valveArray.at(1)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(2)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(3)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(4)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(5)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(6)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(7)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(8)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(9)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter2         
            autoSequenceArray.at(0)->setState(AutoSequenceState::Standby);  // Renegade SF Stand
            sensorArray.at(0)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell1pos
            sensorArray.at(1)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell1neg
            sensorArray.at(2)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell2pos
            sensorArray.at(3)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell2neg
            sensorArray.at(4)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell3pos
            sensorArray.at(5)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell3neg
            sensorArray.at(6)->setState(SensorState::Fast);         // Renegade SF Stand - ChamberPT2
            sensorArray.at(7)->setState(SensorState::Fast);         // Renegade SF Stand - ChamberPT1
            sensorArray.at(8)->setState(SensorState::Fast);         // Renegade SF Stand - FuelInletPropSidePT
            sensorArray.at(9)->setState(SensorState::Fast);         // Renegade SF Stand - FuelInjectorPT
            sensorArray.at(10)->setState(SensorState::Fast);        // Renegade SF Stand - LoxInletPropSidePT
            sensorArray.at(11)->setState(SensorState::Medium);        // Renegade SF Stand - MVPneumaticsPT
            sensorArray.at(12)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegFuelPT
            sensorArray.at(13)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegLoxPT
            sensorArray.at(14)->setState(SensorState::Fast);        // Renegade SF Stand - FuelTankPT
            sensorArray.at(15)->setState(SensorState::Fast);        // Renegade SF Stand - LoxTankPT
            sensorArray.at(16)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressFuelPT
            sensorArray.at(17)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressLoxPT
            sensorArray.at(18)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode2
            sensorArray.at(19)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode3
            currentState = State::fireArmed;
            }
            break;
        case command_fire:
            if(currentState == State::fireArmed)
            {
            valveArray.at(0)->setState(ValveState::CloseCommanded);          // Renegade SF Stand
            valveArray.at(1)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(2)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(3)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(4)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(5)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(6)->setState(ValveState::OpenCommanded);          // Renegade SF Stand
            valveArray.at(7)->setState(ValveState::CloseCommanded);         // Renegade SF Stand
            valveArray.at(8)->setState(ValveState::FireCommanded);          // Renegade SF Stand
            valveArray.at(9)->setState(ValveState::FireCommanded);          // Renegade SF Stand
            pyroArray.at(0)->setState(PyroState::FireCommanded);             // Renegade SF Igniter1
            pyroArray.at(1)->setState(PyroState::FireCommanded);             // Renegade SF Igniter2
            autoSequenceArray.at(0)->setState(AutoSequenceState::RunCommanded);     // Renegade SF Stand
            sensorArray.at(0)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell1pos
            sensorArray.at(1)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell1neg
            sensorArray.at(2)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell2pos
            sensorArray.at(3)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell2neg
            sensorArray.at(4)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell3pos
            sensorArray.at(5)->setState(SensorState::Fast);         // Renegade SF Stand - ThrustMountLoadCell3neg
            sensorArray.at(6)->setState(SensorState::Fast);         // Renegade SF Stand - ChamberPT2
            sensorArray.at(7)->setState(SensorState::Fast);         // Renegade SF Stand - ChamberPT1
            sensorArray.at(8)->setState(SensorState::Fast);         // Renegade SF Stand - FuelInletPropSidePT
            sensorArray.at(9)->setState(SensorState::Fast);         // Renegade SF Stand - FuelInjectorPT
            sensorArray.at(10)->setState(SensorState::Fast);        // Renegade SF Stand - LoxInletPropSidePT
            sensorArray.at(11)->setState(SensorState::Medium);        // Renegade SF Stand - MVPneumaticsPT
            sensorArray.at(12)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegFuelPT
            sensorArray.at(13)->setState(SensorState::Fast);        // Renegade SF Stand - DomeRegLoxPT
            sensorArray.at(14)->setState(SensorState::Fast);        // Renegade SF Stand - FuelTankPT
            sensorArray.at(15)->setState(SensorState::Fast);        // Renegade SF Stand - LoxTankPT
            sensorArray.at(16)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressFuelPT
            sensorArray.at(17)->setState(SensorState::Fast);        // Renegade SF Stand - HiPressLoxPT
            sensorArray.at(18)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode2
            sensorArray.at(19)->setState(SensorState::Medium);        // Renegade SF Stand - MCUtempNode3
            currentState = State::fire;
            }
            break;


        case command_closeHiPress:
            if(currentState == State::test)
            {
                valveArray.at(0)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(0)->setState(ValveState::CloseCommanded);
            }
            break;
        case command_openHiPress:
             if(currentState == State::test)
            {
                valveArray.at(0)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(0)->setState(ValveState::OpenCommanded);
            }
            break;
        case command_closeHiPressVent:
            if(currentState == State::test)
            {
                valveArray.at(1)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(1)->setState(ValveState::CloseCommanded);
            }            
            break;
        case command_openHiPressVent:
             if(currentState == State::test)
            {
                valveArray.at(1)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(1)->setState(ValveState::OpenCommanded);
            }              
            break;
        case command_closeLoxVent:
            if(currentState == State::test)
            {
                valveArray.at(2)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(2)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openLoxVent:
             if(currentState == State::test)
            {
                valveArray.at(2)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(2)->setState(ValveState::OpenCommanded);
            }              
            break;
        case command_closeLoxDomeReg:
            if(currentState == State::test)
            {
                valveArray.at(3)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(3)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openLoxDomeReg:
             if(currentState == State::test)
            {
                valveArray.at(3)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(3)->setState(ValveState::OpenCommanded);
            }              
            break; 
        case command_closeLoxDomeRegVent:
            if(currentState == State::test)
            {
                valveArray.at(4)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(4)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openLoxDomeRegVent:
             if(currentState == State::test)
            {
                valveArray.at(4)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(4)->setState(ValveState::OpenCommanded);
            }              
            break; 
        case command_closeFuelVent:
            if(currentState == State::test)
            {
                valveArray.at(5)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(5)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openFuelVent:
             if(currentState == State::test)
            {
                valveArray.at(5)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(5)->setState(ValveState::OpenCommanded);
            }              
            break;
        case command_closeFuelDomeReg:
            if(currentState == State::test)
            {
                valveArray.at(6)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(6)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openFuelDomeReg:
             if(currentState == State::test)
            {
                valveArray.at(6)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(6)->setState(ValveState::OpenCommanded);
            }              
            break; 
        case command_closeFuelDomeRegVent:
            if(currentState == State::test)
            {
                valveArray.at(7)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(7)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openFuelDomeRegVent:
             if(currentState == State::test)
            {
                valveArray.at(7)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(7)->setState(ValveState::OpenCommanded);
            }              
            break; 
        case command_closeFuelMV:
            if(currentState == State::test)
            {
                valveArray.at(8)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(8)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openFuelMV:
             if(currentState == State::test)
            {
                valveArray.at(8)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(8)->setState(ValveState::OpenCommanded);
            }              
            break;
        case command_closeLoxMV:
            if(currentState == State::test)
            {
                valveArray.at(9)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(9)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openLoxMV:
             if(currentState == State::test)
            {
                valveArray.at(9)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == State::offNominal)
            {
                valveArray.at(9)->setState(ValveState::OpenCommanded);
            }              
            break;
        case command_engineIgniterPyro1_Off:
            if(currentState == State::test)
            {
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            }
            else if (currentState == State::offNominal)
            {
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            }              
            break;
        case command_engineIgniterPyro1_On:
            if(currentState == State::test)
            {
            pyroArray.at(0)->setState(PyroState::OnCommanded);             // Renegade SF Igniter1
            }
            else if (currentState == State::offNominal)
            {
            pyroArray.at(0)->setState(PyroState::OnCommanded);             // Renegade SF Igniter1
            }              
            break;
        case command_engineIgniterPyro2_Off:
            if(currentState == State::test)
            {
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            }
            else if (currentState == State::offNominal)
            {
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            }              
            break;
        case command_engineIgniterPyro2_On:
            if(currentState == State::test)
            {
            pyroArray.at(1)->setState(PyroState::OnCommanded);             // Renegade SF Igniter1
            }
            else if (currentState == State::offNominal)
            {
            pyroArray.at(1)->setState(PyroState::OnCommanded);             // Renegade SF Igniter1
            }              
            break;

        case command_allSensorsOff:
            if(currentState == State::test)
            {
            sensorArray.at(0)->setState(SensorState::Off);         // Renegade SF Stand
            sensorArray.at(1)->setState(SensorState::Off);         // Renegade SF Stand
            sensorArray.at(2)->setState(SensorState::Off);         // Renegade SF Stand
            sensorArray.at(3)->setState(SensorState::Off);         // Renegade SF Stand
            sensorArray.at(4)->setState(SensorState::Off);         // Renegade SF Stand
            sensorArray.at(5)->setState(SensorState::Off);         // Renegade SF Stand
            sensorArray.at(6)->setState(SensorState::Off);         // Renegade SF Stand
            sensorArray.at(7)->setState(SensorState::Off);         // Renegade SF Stand
            sensorArray.at(8)->setState(SensorState::Off);         // Renegade SF Stand
            sensorArray.at(9)->setState(SensorState::Off);         // Renegade SF Stand
            sensorArray.at(10)->setState(SensorState::Off);        // Renegade SF Stand
            sensorArray.at(11)->setState(SensorState::Off);        // Renegade SF Stand
            sensorArray.at(12)->setState(SensorState::Off);        // Renegade SF Stand
            sensorArray.at(13)->setState(SensorState::Off);        // Renegade SF Stand
            sensorArray.at(14)->setState(SensorState::Off);        // Renegade SF Stand
            sensorArray.at(15)->setState(SensorState::Off);        // Renegade SF Stand
            sensorArray.at(16)->setState(SensorState::Off);        // Renegade SF Stand
            }            
            break;
        case command_allSensorsSlow:
            if(currentState == State::test)
            {
            sensorArray.at(0)->setState(SensorState::Slow);         // Renegade SF Stand
            sensorArray.at(1)->setState(SensorState::Slow);         // Renegade SF Stand
            sensorArray.at(2)->setState(SensorState::Slow);         // Renegade SF Stand
            sensorArray.at(3)->setState(SensorState::Slow);         // Renegade SF Stand
            sensorArray.at(4)->setState(SensorState::Slow);         // Renegade SF Stand
            sensorArray.at(5)->setState(SensorState::Slow);         // Renegade SF Stand
            sensorArray.at(6)->setState(SensorState::Slow);         // Renegade SF Stand
            sensorArray.at(7)->setState(SensorState::Slow);         // Renegade SF Stand
            sensorArray.at(8)->setState(SensorState::Slow);         // Renegade SF Stand
            sensorArray.at(9)->setState(SensorState::Slow);         // Renegade SF Stand
            sensorArray.at(10)->setState(SensorState::Slow);        // Renegade SF Stand
            sensorArray.at(11)->setState(SensorState::Slow);        // Renegade SF Stand
            sensorArray.at(12)->setState(SensorState::Slow);        // Renegade SF Stand
            sensorArray.at(13)->setState(SensorState::Slow);        // Renegade SF Stand
            sensorArray.at(14)->setState(SensorState::Slow);        // Renegade SF Stand
            sensorArray.at(15)->setState(SensorState::Slow);        // Renegade SF Stand
            sensorArray.at(16)->setState(SensorState::Slow);        // Renegade SF Stand
            }             
            break;
        case command_allSensorsMedium:
            if(currentState == State::test)
            {
            sensorArray.at(0)->setState(SensorState::Medium);         // Renegade SF Stand
            sensorArray.at(1)->setState(SensorState::Medium);         // Renegade SF Stand
            sensorArray.at(2)->setState(SensorState::Medium);         // Renegade SF Stand
            sensorArray.at(3)->setState(SensorState::Medium);         // Renegade SF Stand
            sensorArray.at(4)->setState(SensorState::Medium);         // Renegade SF Stand
            sensorArray.at(5)->setState(SensorState::Medium);         // Renegade SF Stand
            sensorArray.at(6)->setState(SensorState::Medium);         // Renegade SF Stand
            sensorArray.at(7)->setState(SensorState::Medium);         // Renegade SF Stand
            sensorArray.at(8)->setState(SensorState::Medium);         // Renegade SF Stand
            sensorArray.at(9)->setState(SensorState::Medium);         // Renegade SF Stand
            sensorArray.at(10)->setState(SensorState::Medium);        // Renegade SF Stand
            sensorArray.at(11)->setState(SensorState::Medium);        // Renegade SF Stand
            sensorArray.at(12)->setState(SensorState::Medium);        // Renegade SF Stand
            sensorArray.at(13)->setState(SensorState::Medium);        // Renegade SF Stand
            sensorArray.at(14)->setState(SensorState::Medium);        // Renegade SF Stand
            sensorArray.at(15)->setState(SensorState::Medium);        // Renegade SF Stand
            sensorArray.at(16)->setState(SensorState::Medium);        // Renegade SF Stand
            }             
            break;
        case command_allSensorsFast:
            if(currentState == State::test)
            {
            sensorArray.at(0)->setState(SensorState::Fast);         // Renegade SF Stand
            sensorArray.at(1)->setState(SensorState::Fast);         // Renegade SF Stand
            sensorArray.at(2)->setState(SensorState::Fast);         // Renegade SF Stand
            sensorArray.at(3)->setState(SensorState::Fast);         // Renegade SF Stand
            sensorArray.at(4)->setState(SensorState::Fast);         // Renegade SF Stand
            sensorArray.at(5)->setState(SensorState::Fast);         // Renegade SF Stand
            sensorArray.at(6)->setState(SensorState::Fast);         // Renegade SF Stand
            sensorArray.at(7)->setState(SensorState::Fast);         // Renegade SF Stand
            sensorArray.at(8)->setState(SensorState::Fast);         // Renegade SF Stand
            sensorArray.at(9)->setState(SensorState::Fast);         // Renegade SF Stand
            sensorArray.at(10)->setState(SensorState::Fast);        // Renegade SF Stand
            sensorArray.at(11)->setState(SensorState::Fast);        // Renegade SF Stand
            sensorArray.at(12)->setState(SensorState::Fast);        // Renegade SF Stand
            sensorArray.at(13)->setState(SensorState::Fast);        // Renegade SF Stand
            sensorArray.at(14)->setState(SensorState::Fast);        // Renegade SF Stand
            sensorArray.at(15)->setState(SensorState::Fast);        // Renegade SF Stand
            sensorArray.at(16)->setState(SensorState::Fast);        // Renegade SF Stand
            }            
            break;
        case command_allSensorsCalibration:
            if(currentState == State::test)
            {
            sensorArray.at(0)->setState(SensorState::Calibration);         // Renegade SF Stand
            sensorArray.at(1)->setState(SensorState::Calibration);         // Renegade SF Stand
            sensorArray.at(2)->setState(SensorState::Calibration);         // Renegade SF Stand
            sensorArray.at(3)->setState(SensorState::Calibration);         // Renegade SF Stand
            sensorArray.at(4)->setState(SensorState::Calibration);         // Renegade SF Stand
            sensorArray.at(5)->setState(SensorState::Calibration);         // Renegade SF Stand
            sensorArray.at(6)->setState(SensorState::Calibration);         // Renegade SF Stand
            sensorArray.at(7)->setState(SensorState::Calibration);         // Renegade SF Stand
            sensorArray.at(8)->setState(SensorState::Calibration);         // Renegade SF Stand
            sensorArray.at(9)->setState(SensorState::Calibration);         // Renegade SF Stand
            sensorArray.at(10)->setState(SensorState::Calibration);        // Renegade SF Stand
            sensorArray.at(11)->setState(SensorState::Calibration);        // Renegade SF Stand
            sensorArray.at(12)->setState(SensorState::Calibration);        // Renegade SF Stand
            sensorArray.at(13)->setState(SensorState::Calibration);        // Renegade SF Stand
            sensorArray.at(14)->setState(SensorState::Calibration);        // Renegade SF Stand
            sensorArray.at(15)->setState(SensorState::Calibration);        // Renegade SF Stand
            sensorArray.at(16)->setState(SensorState::Calibration);        // Renegade SF Stand
            }            
            break;
        default:
            break;
    }
}

// state machine for the mission state (launch, ascent, apogee, descent et cetera)
void missionStateMachine(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, bool &HaltFlag)
{

}

// Controller for bang on/off tank pressurization
void bangerPress(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray)
{

}

// Controller for roll control RCS
void rollRCS(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray)
{

}

// Controller for TVC
void thrustVectorControl(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray)
{

}