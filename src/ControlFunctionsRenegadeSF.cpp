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
#define Engine1TVC_Z_ArrayPointer 1

// tank press controller defines for pointers
#define HighPressTankController_ArrayPointer 0
#define LoxTankController_ArrayPointer 1
#define FuelTankController_ArrayPointer 2

// engine controller defines for pointers
#define Engine1Controller_ArrayPointer 0

// -------------------------------------------------------------

void startupStateCheck(const VehicleState& currentState, Command& currentCommand)
{
    switch (currentState)
    {
    case VehicleState::passive:
        currentCommand = command_passive;
        break;
    case VehicleState::test:
        currentCommand = command_test;
        break;
    case VehicleState::HiPressArm:
        currentCommand = command_HiPressArm;
        break;
    case VehicleState::HiPressPressurized:
        currentCommand = command_HiPressPressurized;
        break;
    case VehicleState::TankPressArm:
        currentCommand = command_TankPressArm;
        break;
    case VehicleState::TankPressPressurized:
        currentCommand = commend_TankPressPressurized;
        break;
    case VehicleState::fireArmed:
        currentCommand = command_fireArm;
        break;
    case VehicleState::fire: // if we powercycle mid fire, we just vent (maybe shouldn't always be true with multinode systems)
        currentCommand = command_abort;
        break;
    case VehicleState::abort:
        currentCommand = command_abort;
        break;
    case VehicleState::vent:
        currentCommand = command_vent;
        break;
    default:
        break;
    }
}


void vehicleStateMachine(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, const std::array<TankPressController*, NUM_TANKPRESSCONTROLLERS>& tankPressControllerArray, const std::array<EngineController*, NUM_ENGINECONTROLLERS>& engineControllerArray, bool & haltFlag)
{
    switch (currentCommand)
    {
        case command_debug:
            currentState = VehicleState::debug;
            break;
        case command_passive:
            autoSequenceArray.at(0)->setState(AutoSequenceState::Hold);
            tankPressControllerArray.at(HighPressTankController_ArrayPointer)->setState(TankPressControllerState::Passive);
            tankPressControllerArray.at(LoxTankController_ArrayPointer)->setState(TankPressControllerState::Passive);
            tankPressControllerArray.at(FuelTankController_ArrayPointer)->setState(TankPressControllerState::Passive);
            engineControllerArray.at(Engine1Controller_ArrayPointer)->setState(EngineControllerState::Passive);
            currentState = VehicleState::passive;
            haltFlag = false;
            break;
        case command_test:
            if(currentState == VehicleState::passive)
            {
            currentState = VehicleState::test;
            }
            break;
        case command_EnterOffNominal:
            priorState = currentState; //for remembering the state the system was in when entering Off Nominal
            currentState = VehicleState::offNominal;
            break;            
        case command_ExitOffNominal:
            if(currentState == VehicleState::offNominal)
            {
            currentState = priorState;              //IS THIS STILL TRUE???? - Beware, this currently doesn't function fully as desired. Will leave ValveEnables all on and not actually enter the prior command
            }
            break;
        case command_abort:
            haltFlag = true;
            currentState = VehicleState::abort;
            autoSequenceArray.at(0)->setState(AutoSequenceState::Hold);
            break;
        case command_vent:
            autoSequenceArray.at(0)->setState(AutoSequenceState::Hold);
            tankPressControllerArray.at(HighPressTankController_ArrayPointer)->setState(TankPressControllerState::Passive);
            tankPressControllerArray.at(LoxTankController_ArrayPointer)->setState(TankPressControllerState::Vent);
            tankPressControllerArray.at(FuelTankController_ArrayPointer)->setState(TankPressControllerState::Vent);
            engineControllerArray.at(Engine1Controller_ArrayPointer)->setState(EngineControllerState::Passive);
            currentState = VehicleState::vent;
            break;
// Fire Sequence commands will only be executed from the proper state
        case command_HiPressArm:
            if(currentState == VehicleState::passive)
            {
            autoSequenceArray.at(0)->setState(AutoSequenceState::Standby);
            tankPressControllerArray.at(HighPressTankController_ArrayPointer)->setState(TankPressControllerState::Armed);
            tankPressControllerArray.at(LoxTankController_ArrayPointer)->setState(TankPressControllerState::Passive);
            tankPressControllerArray.at(FuelTankController_ArrayPointer)->setState(TankPressControllerState::Passive);
            engineControllerArray.at(Engine1Controller_ArrayPointer)->setState(EngineControllerState::Passive);
            currentState = VehicleState::HiPressArm;
            }
            break;
        case command_HiPressPressurized:
            if(currentState == VehicleState::HiPressArm || currentState == VehicleState::TankPressArm) //added second conditional to allow entry backwards in a "disarm" state change
            {
            autoSequenceArray.at(0)->setState(AutoSequenceState::Standby);
            tankPressControllerArray.at(HighPressTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            tankPressControllerArray.at(LoxTankController_ArrayPointer)->setState(TankPressControllerState::Passive);
            tankPressControllerArray.at(FuelTankController_ArrayPointer)->setState(TankPressControllerState::Passive);
            engineControllerArray.at(Engine1Controller_ArrayPointer)->setState(EngineControllerState::Passive);
            currentState = VehicleState::HiPressPressurized;
            }
            break;
        case command_TankPressArm:
            if(currentState == VehicleState::HiPressPressurized)
            {
            autoSequenceArray.at(0)->setState(AutoSequenceState::Standby);
            tankPressControllerArray.at(HighPressTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            tankPressControllerArray.at(LoxTankController_ArrayPointer)->setState(TankPressControllerState::Armed);
            tankPressControllerArray.at(FuelTankController_ArrayPointer)->setState(TankPressControllerState::Armed);
            engineControllerArray.at(Engine1Controller_ArrayPointer)->setState(EngineControllerState::Passive);
            currentState = VehicleState::TankPressArm;
            }
            break;
        case commend_TankPressPressurized:
            if(currentState == VehicleState::TankPressArm)
            {
            autoSequenceArray.at(0)->setState(AutoSequenceState::Standby);
            tankPressControllerArray.at(HighPressTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            tankPressControllerArray.at(LoxTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            tankPressControllerArray.at(FuelTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            engineControllerArray.at(Engine1Controller_ArrayPointer)->setState(EngineControllerState::Passive);
            currentState = VehicleState::TankPressPressurized;
            }
            break;
        case command_fireArm:
            if(currentState == VehicleState::TankPressPressurized)
            {
            autoSequenceArray.at(0)->setState(AutoSequenceState::Standby);
            tankPressControllerArray.at(HighPressTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            tankPressControllerArray.at(LoxTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            tankPressControllerArray.at(FuelTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            engineControllerArray.at(Engine1Controller_ArrayPointer)->setState(EngineControllerState::Passive);
            currentState = VehicleState::fireArmed;
            }
            break;
        case command_fire:
            if(currentState == VehicleState::fireArmed)
            {
            autoSequenceArray.at(0)->setState(AutoSequenceState::RunCommanded);            
            tankPressControllerArray.at(HighPressTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            tankPressControllerArray.at(LoxTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            tankPressControllerArray.at(FuelTankController_ArrayPointer)->setState(TankPressControllerState::DomePressActive);
            engineControllerArray.at(Engine1Controller_ArrayPointer)->setState(EngineControllerState::AutosequenceCommanded);
            currentState = VehicleState::fire;
            }
            break;
        case command_closeHiPress:
            if(currentState == VehicleState::test)
            {
                valveArray.at(0)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(0)->setState(ValveState::CloseCommanded);
            }
            break;
        case command_openHiPress:
             if(currentState == VehicleState::test)
            {
                valveArray.at(0)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(0)->setState(ValveState::OpenCommanded);
            }
            break;
        case command_closeHiPressVent:
            if(currentState == VehicleState::test)
            {
                valveArray.at(1)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(1)->setState(ValveState::CloseCommanded);
            }            
            break;
        case command_openHiPressVent:
             if(currentState == VehicleState::test)
            {
                valveArray.at(1)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(1)->setState(ValveState::OpenCommanded);
            }              
            break;
        case command_closeLoxVent:
            if(currentState == VehicleState::test)
            {
                valveArray.at(2)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(2)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openLoxVent:
             if(currentState == VehicleState::test)
            {
                valveArray.at(2)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(2)->setState(ValveState::OpenCommanded);
            }              
            break;
        case command_closeLoxDomeReg:
            if(currentState == VehicleState::test)
            {
                valveArray.at(3)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(3)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openLoxDomeReg:
             if(currentState == VehicleState::test)
            {
                valveArray.at(3)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(3)->setState(ValveState::OpenCommanded);
            }              
            break; 
        case command_closeLoxDomeRegVent:
            if(currentState == VehicleState::test)
            {
                valveArray.at(4)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(4)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openLoxDomeRegVent:
             if(currentState == VehicleState::test)
            {
                valveArray.at(4)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(4)->setState(ValveState::OpenCommanded);
            }              
            break; 
        case command_closeFuelVent:
            if(currentState == VehicleState::test)
            {
                valveArray.at(5)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(5)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openFuelVent:
             if(currentState == VehicleState::test)
            {
                valveArray.at(5)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(5)->setState(ValveState::OpenCommanded);
            }              
            break;
        case command_closeFuelDomeReg:
            if(currentState == VehicleState::test)
            {
                valveArray.at(6)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(6)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openFuelDomeReg:
             if(currentState == VehicleState::test)
            {
                valveArray.at(6)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(6)->setState(ValveState::OpenCommanded);
            }              
            break; 
        case command_closeFuelDomeRegVent:
            if(currentState == VehicleState::test)
            {
                valveArray.at(7)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(7)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openFuelDomeRegVent:
             if(currentState == VehicleState::test)
            {
                valveArray.at(7)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(7)->setState(ValveState::OpenCommanded);
            }              
            break; 
        case command_closeFuelMV:
            if(currentState == VehicleState::test)
            {
                valveArray.at(8)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(8)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openFuelMV:
             if(currentState == VehicleState::test)
            {
                valveArray.at(8)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(8)->setState(ValveState::OpenCommanded);
            }              
            break;
        case command_closeLoxMV:
            if(currentState == VehicleState::test)
            {
                valveArray.at(9)->setState(ValveState::CloseCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(9)->setState(ValveState::CloseCommanded);
            }              
            break;
        case command_openLoxMV:
             if(currentState == VehicleState::test)
            {
                valveArray.at(9)->setState(ValveState::OpenCommanded);
            }
            else if (currentState == VehicleState::offNominal)
            {
                valveArray.at(9)->setState(ValveState::OpenCommanded);
            }              
            break;
        case command_engineIgniterPyro1_Off:
            if(currentState == VehicleState::test)
            {
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            }
            else if (currentState == VehicleState::offNominal)
            {
            pyroArray.at(0)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            }              
            break;
        case command_engineIgniterPyro1_On:
            if(currentState == VehicleState::test)
            {
            pyroArray.at(0)->setState(PyroState::OnCommanded);             // Renegade SF Igniter1
            }
            else if (currentState == VehicleState::offNominal)
            {
            pyroArray.at(0)->setState(PyroState::OnCommanded);             // Renegade SF Igniter1
            }              
            break;
        case command_engineIgniterPyro2_Off:
            if(currentState == VehicleState::test)
            {
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            }
            else if (currentState == VehicleState::offNominal)
            {
            pyroArray.at(1)->setState(PyroState::OffCommanded);             // Renegade SF Igniter1
            }              
            break;
        case command_engineIgniterPyro2_On:
            if(currentState == VehicleState::test)
            {
            pyroArray.at(1)->setState(PyroState::OnCommanded);             // Renegade SF Igniter1
            }
            else if (currentState == VehicleState::offNominal)
            {
            pyroArray.at(1)->setState(PyroState::OnCommanded);             // Renegade SF Igniter1
            }              
            break;

        case command_allSensorsOff:
            if(currentState == VehicleState::test)
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
            if(currentState == VehicleState::test)
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
            if(currentState == VehicleState::test)
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
            if(currentState == VehicleState::test)
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
            if(currentState == VehicleState::test)
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

///// ----- NEW FUNCTIONS, WORK IN PROGRESS ----- /////

// state machine for the mission state (launch, ascent, apogee, descent et cetera)
void missionStateMachine(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, bool &HaltFlag)
{

}

void controllerDeviceSync(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, const std::array<TankPressController*, NUM_TANKPRESSCONTROLLERS>& tankPressControllerArray, const std::array<EngineController*, NUM_ENGINECONTROLLERS>& engineControllerArray, bool & haltFlag)
{
    //Serial.println("Is this even on???");
        // COPV
        valveArray.at(HiPress_ArrayPointer)->setState(tankPressControllerArray.at(HighPressTankController_ArrayPointer)->getPrimaryPressValveState());
        valveArray.at(HiPressVent_ArrayPointer)->setState(tankPressControllerArray.at(HighPressTankController_ArrayPointer)->getPressLineVentState());
        // Lox Tank
        valveArray.at(LoxDomeReg_ArrayPointer)->setState(tankPressControllerArray.at(LoxTankController_ArrayPointer)->getPrimaryPressValveState());
        valveArray.at(LoxDomeRegVent_ArrayPointer)->setState(tankPressControllerArray.at(LoxTankController_ArrayPointer)->getPressLineVentState());
        valveArray.at(LoxVent_ArrayPointer)->setState(tankPressControllerArray.at(LoxTankController_ArrayPointer)->getTankVentState());
        // Fuel Tank
        valveArray.at(FuelDomeReg_ArrayPointer)->setState(tankPressControllerArray.at(FuelTankController_ArrayPointer)->getPrimaryPressValveState());
        valveArray.at(FuelDomeRegVent_ArrayPointer)->setState(tankPressControllerArray.at(FuelTankController_ArrayPointer)->getPressLineVentState());
        valveArray.at(FuelVent_ArrayPointer)->setState(tankPressControllerArray.at(FuelTankController_ArrayPointer)->getTankVentState());
        // Engine 1
        valveArray.at(FuelDomeReg_ArrayPointer)->setState(engineControllerArray.at(Engine1Controller_ArrayPointer)->getPilotMVFuelValveState());
        valveArray.at(FuelDomeRegVent_ArrayPointer)->setState(engineControllerArray.at(Engine1Controller_ArrayPointer)->getPilotMVLoxValveState());
        valveArray.at(FuelVent_ArrayPointer)->setState(engineControllerArray.at(Engine1Controller_ArrayPointer)->getPneumaticVentState());
        pyroArray.at(FuelDomeReg_ArrayPointer)->setState(engineControllerArray.at(Engine1Controller_ArrayPointer)->getIgniter1State());
        pyroArray.at(FuelDomeRegVent_ArrayPointer)->setState(engineControllerArray.at(Engine1Controller_ArrayPointer)->getIgniter2State());

    // Print Statement for debugging
    //Serial.print(static_cast<uint8_t>(valveArray.at(LoxVent_ArrayPointer)->getState()));
}