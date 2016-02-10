/**********************************************************
 * This file is generated by 20-sim ANSI-C Code Generator
 *
 *  file:  src\xxmodel.c
 *  model: threetank
 *  expmt: threetank
 *  date:  February 3, 2016
 *  time:  2:33:24 PM
 *  user:  Controllab Internal
 *  from:  Controllab Products B.V., 20-sim 4.7 Professional Single
 *  build: 4.7.1000.6732
 **********************************************************/

/* This file contains the actual model variables and equations */

/* Note: Alias variables are the result of full optimization
   of the model in 20-sim. As a result, only the real variables
   are used in the model for speed. The user may also include
   the alias variables by adding them to the end of the array:

   XXDouble xx_variables[NUMBER_VARIABLES + NUMBER_ALIAS_VARIABLES + 1];
   XXCharacter *xx_variable_names[] = {
     VARIABLE_NAMES, ALIAS_VARIABLE_NAMES, NULL
   };

   and calculate them directly after the output equations:

   void XXCalculateOutput (void)
   {
     OUTPUT_EQUATIONS
     ALIAS_EQUATIONS
   }
*/

/* system include files */
#include <stdlib.h>
#include <math.h>

/* 20-sim include files */
#include "xxmodel.h"
#include "xxfuncs.h"

/* the global variables */
XXDouble xx_start_time = 0.0;
XXDouble xx_finish_time = 20.0;
XXDouble xx_step_size = 0.02;
XXDouble xx_time = 0.0;
XXInteger xx_steps = 0;
XXBoolean xx_initialize = XXTRUE;
XXBoolean xx_major = XXTRUE;
XXBoolean xx_stop_simulation = XXFALSE;

/* the variable arrays */
XXDouble xx_MEMORY[0 + 10 + 4 + 17 + 4 + 4 + 1];
XXDouble* xx_C = xx_MEMORY;		/* constants */
XXDouble* xx_P = xx_MEMORY + 0;			/* parameters */
XXDouble* xx_I = xx_MEMORY + 0 + 10;		/* initial values */
XXDouble* xx_V = xx_MEMORY + 0 + 10 + 4;		/* variables */
XXDouble* xx_s = xx_MEMORY + 0 + 10 + 4 + 17;		/* states */
XXDouble *xx_R = xx_MEMORY + 0 + 10 + 4 + 17 + 4;		/* rates (or new states) */

/* the names of the variables as used in the arrays above
   uncomment this part if these names are needed
XXCharacter *xx_parameter_names[] = {
	"Inflow\\PulseWave\\interval",
	"Inflow\\PulseWave\\pulselength",
	"Inflow\\PulseWave\\amplitude",
	"Pipe\\I\\massInPipe",
	"Pipe\\R\\r",
	"WaterTank1\\Tank1\\area",
	"WaterTank2\\I1\\i",
	"WaterTank2\\R1\\r",
	"WaterTank2\\Tank2\\area",
	"WaterTank2\\Tank2\\upperPortHeight"
,	NULL
};
XXCharacter *xx_initial_value_names[] = {
	"Pipe\\I\\state_initial",
	"",
	"WaterTank2\\I1\\state_initial",
	"WaterTank2\\Tank2\\state_initial"
,	NULL
};
XXCharacter *xx_variable_names[] = {
	"Inflow\\PulseWave\\output",
	"",
	"",
	"",
	"Pipe\\I\\p.f",
	"Pipe\\I\\i",
	"Pipe\\R\\p.e",
	"WaterTank1\\Tank1\\p.e",
	"WaterTank1\\ZeroJunction\\p1.f",
	"WaterTank2\\I1\\p.f",
	"WaterTank2\\R1\\p.e",
	"WaterTank2\\Tank2\\lowerPort.e",
	"WaterTank2\\Tank2\\upperPort.e",
	"Tank1WaterLevel",
	"Tank2WaterLevel",
	"Tank1InFlow",
	"Tank2OutFlow"
,	NULL
};
XXCharacter *xx_state_names[] = {
	"Pipe\\I\\state",
	"WaterTank1\\Tank1\\state",
	"WaterTank2\\I1\\state",
	"WaterTank2\\Tank2\\state"
,	NULL
};
XXCharacter *xx_rate_names[] = {
	"Pipe\\I\\p.e",
	"WaterTank1\\Tank1\\state_dot",
	"WaterTank2\\I1\\p.e",
	"WaterTank2\\Tank2\\state_dot"
,	NULL
};
*/

/* this method is called before calculation is possible */
void XXModelInitialize (void)
{
	/* set the parameters */
	xx_P[0] = 0.2;		/* Inflow\PulseWave\interval {s} */
	xx_P[1] = 0.1;		/* Inflow\PulseWave\pulselength {s} */
	xx_P[2] = 1.0;		/* Inflow\PulseWave\amplitude */
	xx_P[3] = 0.1;		/* Pipe\I\massInPipe */
	xx_P[4] = 150.0;		/* Pipe\R\r */
	xx_P[5] = 0.001;		/* WaterTank1\Tank1\area */
	xx_P[6] = 100.0;		/* WaterTank2\I1\i */
	xx_P[7] = 5000.0;		/* WaterTank2\R1\r */
	xx_P[8] = 0.001;		/* WaterTank2\Tank2\area */
	xx_P[9] = 500.0;		/* WaterTank2\Tank2\upperPortHeight */


	/* set the initial values */
	xx_I[0] = 0.0;		/* Pipe\I\state_initial */
	xx_I[1] = 1.0e-6;		/* WaterTank1\Tank1\state_initial */
	xx_I[2] = 0.0;		/* WaterTank2\I1\state_initial */
	xx_I[3] = 0.0;		/* WaterTank2\Tank2\state_initial */


	/* set the states */
	xx_s[0] = xx_I[0];		/* Pipe\I\state */
	xx_s[1] = xx_I[1];		/* WaterTank1\Tank1\state */
	xx_s[2] = xx_I[2];		/* WaterTank2\I1\state */
	xx_s[3] = xx_I[3];		/* WaterTank2\Tank2\state */


}

/* This function calculates the initial equations of the model.
 * These equations are calculated before anything else
 */
void XXCalculateInitial (void)
{

		/* if Inflow\PulseWave\pulselength >= Inflow\PulseWave\interval */
		if (xx_P[1] >= xx_P[0])
		{
			/* stopsimulation */
			XXStopSimulation ( "pulselength should be smaller than interval", 0);

		}

		/* Inflow\PulseWave\x = 1.0; */
		xx_V[1] = 1.0;

		/* Inflow\PulseWave\nextTime = starttime; */
		xx_V[2] = xx_start_time;

		/* Pipe\I\i = 1.0e-13; */
		xx_V[5] = 1.0e-13;

}

/* This function calculates the static equations of the model.
 * These equations are only dependent from parameters and constants
 */
void XXCalculateStatic (void)
{
	/* Pipe\I\i = 1; */
	xx_V[5] = 1.0;

}

/* This function calculates the input equations of the model.
 * These equations are dynamic equations that must not change
 * in calls from the integration method (like random and delay).
 */
void XXCalculateInput (void)
{

}

/* This function calculates the dynamic equations of the model.
 * These equations are called from the integration method
 * to calculate the new model rates (that are then integrated).
 */
void XXCalculateDynamic (void)
{
	/* Pipe\I\p.f = Pipe\I\state / Pipe\I\i; */
	xx_V[4] = xx_s[0] / xx_V[5];

	/* WaterTank1\Tank1\p.e = WaterTank1\Tank1\state / WaterTank1\Tank1\area; */
	xx_V[7] = xx_s[1] / xx_P[5];

	/* WaterTank2\I1\p.f = WaterTank2\I1\state / WaterTank2\I1\i; */
	xx_V[9] = xx_s[2] / xx_P[6];

	/* WaterTank2\Tank2\lowerPort.e = WaterTank2\Tank2\state / WaterTank2\Tank2\area; */
	xx_V[11] = xx_s[3] / xx_P[8];

	/* if ((WaterTank2\Tank2\state / WaterTank2\Tank2\area) > WaterTank2\Tank2\upperPortHeight) */
	if ((xx_s[3] / xx_P[8]) > xx_P[9])
	{
		/* WaterTank2\Tank2\upperPort.e = (WaterTank2\Tank2\state / WaterTank2\Tank2\area) - WaterTank2\Tank2\upperPortHeight; */
		xx_V[12] = (xx_s[3] / xx_P[8]) - xx_P[9];
	}
	else
	{
		/* WaterTank2\Tank2\upperPort.e = 0.0; */
		xx_V[12] = 0.0;
	}

	/* Pipe\R\p.e = Pipe\R\r * Pipe\I\p.f; */
	xx_V[6] = xx_P[4] * xx_V[4];

	/* WaterTank2\R1\p.e = WaterTank2\R1\r * WaterTank2\I1\p.f; */
	xx_V[10] = xx_P[7] * xx_V[9];

	/* Pipe\I\p.e = (WaterTank1\Tank1\p.e - WaterTank2\Tank2\lowerPort.e) - Pipe\R\p.e; */
	xx_R[0] = (xx_V[7] - xx_V[11]) - xx_V[6];

	/* WaterTank1\ZeroJunction\p1.f = -Pipe\I\p.f; */
	xx_V[8] = -xx_V[4];

	/* WaterTank2\I1\p.e = WaterTank2\Tank2\upperPort.e - WaterTank2\R1\p.e; */
	xx_R[2] = xx_V[12] - xx_V[10];

	/* WaterTank2\Tank2\state_dot = Pipe\I\p.f - WaterTank2\I1\p.f; */
	xx_R[3] = xx_V[4] - xx_V[9];

		/* Inflow\PulseWave\timetrigger = timeevent (Inflow\PulseWave\nextTime); */
		xx_V[3] = XXTimeEvent (xx_V[2], 0);

		/* if (time >= Inflow\PulseWave\nextTime) */
		if (xx_time >= xx_V[2])
		{
			/* if Inflow\PulseWave\x == 0.0 */
			if (xx_V[1] == 0.0)
			{
				/* Inflow\PulseWave\output = 1.0; */
				xx_V[0] = 1.0;
			}
			else
			{
				/* Inflow\PulseWave\output = 0.0; */
				xx_V[0] = 0.0;
			}

			/* if major */
			if (xx_major)
			{
				/* Inflow\PulseWave\x = Inflow\PulseWave\output; */
				xx_V[1] = xx_V[0];

				/* if (Inflow\PulseWave\x == 0.0) */
				if (xx_V[1] == 0.0)
				{
					/* Inflow\PulseWave\nextTime = (time + Inflow\PulseWave\interval) - Inflow\PulseWave\pulselength; */
					xx_V[2] = (xx_time + xx_P[0]) - xx_P[1];
				}
				else
				{
					/* Inflow\PulseWave\nextTime = time + Inflow\PulseWave\pulselength; */
					xx_V[2] = xx_time + xx_P[1];
				}
			}
		}
		else
		{
			/* Inflow\PulseWave\output = Inflow\PulseWave\amplitude * Inflow\PulseWave\x; */
			xx_V[0] = xx_P[2] * xx_V[1];
		}

	/* WaterTank1\Tank1\state_dot = WaterTank1\ZeroJunction\p1.f + Inflow\PulseWave\output; */
	xx_R[1] = xx_V[8] + xx_V[0];


	/* increment the step counter */
	xx_steps++;
}

/* This function calculates the output equations of the model.
 * These equations are not needed for calculation of the rates
 * and are kept separate to make the dynamic set of equations smaller.
 * These dynamic equations are called often more than one time for each
 * integration step that is taken. This makes model computation much faster.
 */
void XXCalculateOutput (void)
{
	/* Tank1WaterLevel = WaterTank1\Tank1\state; */
	xx_V[13] = xx_s[1];

	/* Tank2WaterLevel = WaterTank2\Tank2\state; */
	xx_V[14] = xx_s[3];

	/* Tank2OutFlow = WaterTank2\I1\p.f; */
	xx_V[16] = xx_V[9];

	/* Tank1InFlow = Inflow\PulseWave\output; */
	xx_V[15] = xx_V[0];

}

/* This function calculates the final equations of the model.
 * These equations are calculated after all the calculations
 * are performed
 */
void XXCalculateFinal (void)
{

}

/* this method is called after all calculations are performed */
void XXModelTerminate(void)
{
}


