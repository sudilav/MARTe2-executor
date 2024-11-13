/**
 * @file VariableEndGAM.h
 * @brief Header file for class VariableEndGAM
 * @date 11/07/2022
 * @author Edward Jones
 *
 *
 * @warning Unless required by applicable law or agreed to in writing, 
 * software distributed under the Licence is distributed on an "AS IS"
 * basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the Licence permissions and limitations under the Licence.

 * @details This header file contains the declaration of the class VariableEndGAM
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef ENDGAM_H_
#define ENDGAM_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "GAM.h"
#include "TypeDescriptor.h"
#include "Message.h"
/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {
/**
 *
 */
/**

        +EndGAM = {
            Class = EndGAM
            MaxCycles = 40
            InputSignals = {
                dummySignal = { // Not used but needs to be here to avoid errors
                    DataSource = DDB1
                    Type = float64 // Doesn't actually matter since we never read this.
                }
            }
        }
**/        
class EndGAM : public GAM {
public:
    CLASS_REGISTER_DECLARATION()
    /**
     * @brief Constructor. NOOP.
     */
        EndGAM();

    /**
     * @brief Destructor. NOOP.
     */
    virtual ~EndGAM();

    /**
     * @brief Reads the Gain from the configuration file.
     * @param[in] data see GAM::Initialise. The parameter Gains shall exist and will be read as an uint32 array (one value for each output signal).
     * @return true if the parameter Gain can be read.
     */
    virtual bool Initialise(StructuredDataI & data);

    /**
     * @brief Verifies correctness of the GAM configuration.
     * @details Checks that the number of input signals is equal to 4 and the number of output signals is equal to one and that the same type is used.
     * @return true if the pre-conditions are met.
     * @pre
     *   SetConfiguredDatabase() &&
     *   GetNumberOfInputSignals() == 4 && GetNumberOfOutputSignals() >= 4 &&
     *   GetSignalType(InputSignals, 0) == GetSignalType(OutputSignals, *) == float64 &&
     *   GetSignalNumberOfDimensions(InputSignals, *) == GetSignalNumberOfDimensions(OutputSignals, 0) == 0 &&
     *   GetSignalNumberOfSamples(InputSignals, *) == GetSignalNumberOfSamples(OutputSignals, 0) == 1 &&
     *   GetSignalNumberOfElements(InputSignals, *) == GetSignalNumberOfElements(OutputSignals, 0) == 1
     */
    virtual bool Setup();

    /**
     * @brief Multiplies the input signal by the Gain, adds the result to the total.
     * @return true.
     */
    virtual bool Execute();

protected:
    /**
     * The input signals
     */
    float64* dummySignal;
    /**
     * The configured maxcycles.
     */
    uint64 maxcycles;
    uint64 cyclecount;
    bool triggered;
};
}
/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* EXAMPLES_CORE_VARIABLEGAMEXAMPLE1_H_ */
