 /*
 * @file EndGAM.cpp
 * @brief Source file for class EndGAM
 * @date 06/04/2018
 * @author Andre Neto
 *
 * @copyright Copyright 2015 F4E | European Joint Undertaking for ITER and
 * the Development of Fusion Energy ('Fusion for Energy').
 * Licensed under the EUPL, Version 1.1 or - as soon they will be approved
 * by the European Commission - subsequent versions of the EUPL (the "Licence")
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at: http://ec.europa.eu/idabc/eupl
 *
 * @warning Unless required by applicable law or agreed to in writing, 
 * software distributed under the Licence is distributed on an "AS IS"
 * basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the Licence permissions and limitations under the Licence.
 * @details This source file contains the definition of all the methods for
 * the class EndGAM (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "AdvancedErrorManagement.h"
#include "EndGAM.h"
#include "AnyType.h"
#include <signal.h>
/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/
namespace MARTe {
    EndGAM::EndGAM() : GAM(){
    maxcycles = 0ull;
    cyclecount = 0ull;
    triggered = false;
    dummySignal = NULL_PTR(float64*);
}

    EndGAM::~EndGAM() {
}

bool EndGAM::Initialise(MARTe::StructuredDataI & data) {
    bool ok = GAM::Initialise(data);
    if (!ok) {
        REPORT_ERROR(ErrorManagement::ParametersError, "Could not Initialise the GAM");
    }
    if (ok) {
        ok = data.Read("MaxCycles", maxcycles);
        if (!ok) {
            REPORT_ERROR(ErrorManagement::ParametersError, "The parameter MaxCycles could not be read");
        }
    }
    if (ok) {
        REPORT_ERROR(ErrorManagement::Information, "Parameter MaxCycles set to %d", maxcycles);
    }
    return ok;
}


/* used to check the correctness of the config file for a single-input, single-output solution 
 *
 * step 1 - check that the number of of signals is correct
 *
 * step 2 - check the rest of the signals factors are correct
 *
 * step 3 - request memory
 *
 * */
bool EndGAM::Setup() {
    /* ----- Step 3 ---- */
    bool ok = true;
    if (ok) {
        dummySignal = reinterpret_cast<float64*>(GetInputSignalMemory(0u));
    }
    /* ---- if ok = true then GAM is ready, if ok == false then loading fails ----- */
    return ok;
}

bool EndGAM::Execute(){
    // If MaxCycles is set to zero, we do nothing
    if (maxcycles != 0) {
        if ((maxcycles < cyclecount) && !triggered) {
            kill(0, 2);
            triggered = true;
        }
        cyclecount++;
    }

    return true;
}

CLASS_REGISTER(EndGAM, "1.0")
}