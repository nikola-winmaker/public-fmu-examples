/**********************************************************
 * This file is generated by 20-sim ANSI-C Code Generator
 *
 *  file:  src\fmi2Functions.c
 *  model: threetank
 *  expmt: threetank
 *  date:  February 4, 2016
 *  time:  3:14:49 PM
 *  user:  INTO-CPS
 *  from:  20-sim 4.6 Professional Single
 *  build: 4.6.1.6733
 **********************************************************/

/* This file contains the implementation of the FMI functions
   Please check the fmiSunctions.h file for more details
*/

/* The FMI related headers */
#include "fmi2Functions.h"
#include "fmiGUID.h"

/* Our own include files */
#include "xxsubmod.h"

/* The system include files */
#include <string.h>

/* make a FMI_Dll_Export that is for both FMI1 and FMI2 */
#define FMI_Dll_Export FMI2_Export

/* our own component identifier 
   this can become a pointer to a full structure that is filled when instantiating
   for now a simple non-NULL string pointer is returned
*/
#define xxComponent "WaterTankController"

/* Global pointer to co-simulator callback functions */
const fmi2CallbackFunctions* g_fmiCallbackFunctions = NULL;

/* Inquire version numbers of header files */
FMI_Dll_Export const char* fmi2GetTypesPlatform()
{
    return fmi2TypesPlatform;
}
FMI_Dll_Export const char* fmi2GetVersion()
{
    return fmi2Version;
}
FMI_Dll_Export fmi2Status fmi2SetDebugLogging  (fmi2Component c, fmi2Boolean loggingOn,
											size_t nCategories,
											const fmi2String categories[])
{
    return fmi2OK;       /* not yet */
}
/* Data Exchange Functions*/
FMI_Dll_Export fmi2Status fmi2GetReal(fmi2Component c,
									 const fmi2ValueReference vr[],
									 size_t nvr, fmi2Real value[])
{
    size_t i;
    for (i = 0; i < nvr; i++)
    {
        value [i] = xx_MEMORY[ vr[i] ];
    }
    return fmi2OK;
}
FMI_Dll_Export fmi2Status fmi2GetInteger(fmi2Component c,
								const fmi2ValueReference vr[],
								size_t nvr,
								fmi2Integer value[])
{
	/* 20-sim generated C-code uses doubles for the model equation calculations. The variable type (i.e. integer or boolean) are not supported as data type, but are transfered to doubles. In the FMI interface however, the double can be converted to its implicit type  */
	
    size_t i;
    for (i = 0; i < nvr; i++)
    {
        value [i] = (fmi2Integer) xx_MEMORY[ vr[i] ];
    }
    return fmi2OK;
}
FMI_Dll_Export fmi2Status fmi2GetBoolean(fmi2Component c,
								const fmi2ValueReference vr[],
								size_t nvr,
								fmi2Boolean value[])
{
	/* 20-sim generated C-code uses doubles for the model equation calculations. The variable type (i.e. integer or boolean) are not supported as data type, but are transfered to doubles. In the FMI interface however, the double can be converted to its implicit type  */
	
    size_t i;
    for (i = 0; i < nvr; i++)
    {
        value [i] = (xx_MEMORY[ vr[i] ] == 1.0);
    }
    return fmi2OK;
}
FMI_Dll_Export fmi2Status fmi2GetString(fmi2Component c,
								const fmi2ValueReference vr[],
								size_t nvr,
								fmi2String value[])
{
    return fmi2Error;    /* not yet */
}

FMI_Dll_Export fmi2Status fmi2SetReal(fmi2Component c,
								const fmi2ValueReference vr[],
								size_t nvr,
								const fmi2Real value[])
{
    size_t i;
    for (i = 0; i < nvr; i++)
    {
        xx_MEMORY[ vr[i] ] = value [i];
    }
    return fmi2OK;
}

FMI_Dll_Export fmi2Status fmi2SetInteger (fmi2Component c,
								const fmi2ValueReference vr[],
								size_t nvr,
								const fmi2Integer value[])
{
	/* 20-sim generated C-code uses doubles for the model equation calculations. The variable type (i.e. integer or boolean) are not supported as data type, but are transfered to doubles. In the FMI interface however, the double can be converted to its implicit type  */
	
    size_t i;
    for (i = 0; i < nvr; i++)
    {
        xx_MEMORY[ vr[i] ] = (XXDouble) value [i];
    }
    return fmi2OK;
}
FMI_Dll_Export fmi2Status fmi2SetBoolean(fmi2Component c,
								const fmi2ValueReference vr[],
								size_t nvr,
								const fmi2Boolean value[])
{
	/* temp implementation allowing boolean to real conversion, until proper boolean support is added. */
	size_t i;
	for (i = 0; i < nvr; i++)
	{
		xx_MEMORY[vr[i]] = value[i] ? 1.0 : 0.0;
	}
	return fmi2OK;    
}
FMI_Dll_Export fmi2Status fmi2SetString(fmi2Component c,
								const fmi2ValueReference vr[],
								size_t nvr,
								const fmi2String  value[])
{
    return fmi2Error;   /* not yet */
}

fmi2Component fmi2Instantiate(fmi2String instanceName,
								fmi2Type fmuType,
								fmi2String fmuGUID,
								fmi2String fmuResourceLocation,
								const fmi2CallbackFunctions* functions,
								fmi2Boolean visible,
								fmi2Boolean loggingOn)
{
	/* we should remember the functions pointer in order to make callback functions */

    if (!functions)
	{
        return NULL; // we cannot even log this problem
	}
	
    if (!functions->logger)
	{
        return NULL; // we cannot even log this problem
	}
    if (!instanceName || strlen(instanceName)==0) { 
        functions->logger(NULL, "?", fmi2Error, "error",
                "Missing instance name.");
        return NULL;
    }
	else
	{
		/* Register the callback */
		g_fmiCallbackFunctions = functions;
	}
	
	/* Check whether the given GUID equals our GUID */
	if( strncmp(fmuGUID, FMI_GUID, strlen(fmuGUID)) != 0 )
	{
		g_fmiCallbackFunctions->logger(NULL, instanceName, fmi2Error, "error",
			"Wrong GUID %s. Expected %s.", fmuGUID, FMI_GUID);
		return NULL;
	}
	/* check if we are setup for co-simulation, that's the only possible option for now */
	if( fmuType != fmi2CoSimulation )
	{
		g_fmiCallbackFunctions->logger(NULL, instanceName, fmi2Error, "error",
			"FMU can only be used for Co-Simulation, not for Model Exchange");
		return NULL;
	}

    /* only one static instance for now */
    return (fmi2Component) xxComponent;
}
fmi2Status fmi2SetupExperiment(fmi2Component c,
							fmi2Boolean toleranceDefined,
							fmi2Real tolerance,
							fmi2Real startTime,
							fmi2Boolean stopTimeDefined,
							fmi2Real stopTime)
{
    /* copy the arguments */
    xx_start_time = startTime;
    if (stopTimeDefined == fmi2True) 
    {
        xx_finish_time = stopTime;
    }

    /* initialize the submodel itself */
    XXInitializeSubmodel (startTime);

    /* all done */
    return fmi2OK;
}
fmi2Status fmi2EnterInitializationMode(fmi2Component c)
{
   /* nothing to do for now */
   return fmi2OK;
}
fmi2Status fmi2ExitInitializationMode(fmi2Component c)
{
   /* nothing to do for now */
   return fmi2OK;
}
fmi2Status fmi2Terminate(fmi2Component c) 
{
	/* Perform the final calculations */
	XXTerminateSubmodel (xx_time);

    /* all done */
    return fmi2OK;
}
fmi2Status fmi2Reset(fmi2Component c) 
{
    /* initialize the submodel itself */
    XXInitializeSubmodel (xx_start_time);

    /* all done */
    return fmi2OK;
}

void fmi2FreeInstance(fmi2Component c) 
{
    /* only one static instance (done automatically) */
}

fmi2Status fmi2SetRealInputDerivatives(fmi2Component c,
									const fmi2ValueReference vr[], size_t nvr,
									const fmi2Integer order[],
									const fmi2Real value[]) 
{
    /* not yet */
    return fmi2Error;
}

fmi2Status fmi2GetRealOutputDerivatives(fmi2Component c,
									const fmi2ValueReference vr[],
									size_t nvr,
									const fmi2Integer order[],
									fmi2Real value[]) 
{
    /* not yet */
    return fmi2Error;
}

fmi2Status fmi2CancelStep(fmi2Component c) 
{
    /* not yet */
    return fmi2Error;
}

fmi2Status fmi2DoStep(fmi2Component c,
					fmi2Real currentCommunicationPoint,
					fmi2Real communicationStepSize,
					fmi2Boolean noSetFMUStatePriorToCurrentPoint)
{
    /* Treat also case of zero step, i.e. during an event iteration */
    if (communicationStepSize == 0) 
    {
        return fmi2OK;
    }

    /* as long as we are not passed our communication point */
    while (xx_time < (currentCommunicationPoint + communicationStepSize))
    {
        /* check for termination first */
        if ( (xx_finish_time > 0.0) && (xx_time > xx_finish_time) )
        {
			if(g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
			{
				g_fmiCallbackFunctions->logger(NULL, "WaterTankController", fmi2Error, "error",
					"Exceeded model finish time: %g > %g\n", xx_time, xx_finish_time);
			}
			
            /* we're done */
            return fmi2Error;
        }
        
		/* Call the submodel to calculate the output, and increase the time as well */
		XXCalculateSubmodel (xx_time);
    }
    
    /* for now */
    return fmi2OK;
}

fmi2Status fmi2GetStatus(fmi2Component c, const fmi2StatusKind s, fmi2Status* value) 
{
    /* all fine? */
    return fmi2OK;
}

fmi2Status fmi2GetRealStatus(fmi2Component c, const fmi2StatusKind s, fmi2Real* value)
{
    /* all fine? */
    return fmi2OK;
}

fmi2Status fmi2GetIntegerStatus(fmi2Component c, const fmi2StatusKind s, fmi2Integer* value)
{
    /* all fine? */
    return fmi2OK;
}

fmi2Status fmi2GetBooleanStatus(fmi2Component c, const fmi2StatusKind s, fmi2Boolean* value)
{
    /* all fine? */
    return fmi2OK;
}

fmi2Status fmi2GetStringStatus(fmi2Component c, const fmi2StatusKind s, fmi2String*  value)
{
    /* not yet */
    return fmi2Discard;
}

fmi2Status fmi2GetContinuousStates(fmi2Component c, fmi2Real x[], size_t nx)
{
	if( 0 != nx )
	{
		return fmi2Error;
	}
	/* the exported submodel has no states */
	return fmi2OK;
}

fmi2Status fmi2GetFMUstate (fmi2Component c, fmi2FMUstate* FMUstate) {
    
/* not yet */
    return fmi2Discard;
}
fmi2Status fmi2SetFMUstate (fmi2Component c, fmi2FMUstate FMUstate) {
    /* not yet */
    return fmi2Discard;
}
fmi2Status fmi2FreeFMUstate(fmi2Component c, fmi2FMUstate* FMUstate) {
    /* not yet */
    return fmi2Discard;
}
fmi2Status fmi2SerializedFMUstateSize(fmi2Component c, fmi2FMUstate FMUstate, size_t *size) {
    /* not yet */
    return fmi2Discard;
}
fmi2Status fmi2SerializeFMUstate (fmi2Component c, fmi2FMUstate FMUstate, fmi2Byte serializedState[], size_t size) {
    /* not yet */
    return fmi2Discard;
}
fmi2Status fmi2DeSerializeFMUstate (fmi2Component c, const fmi2Byte serializedState[], size_t size,
                                    fmi2FMUstate* FMUstate) {
    /* not yet */
    return fmi2Discard;
}

fmi2Status fmi2GetDirectionalDerivative(fmi2Component c, const fmi2ValueReference vUnknown_ref[], size_t nUnknown,
                                        const fmi2ValueReference vKnown_ref[] , size_t nKnown,
                                        const fmi2Real dvKnown[], fmi2Real dvUnknown[]) {
    /* not yet */
    return fmi2Discard;
}
