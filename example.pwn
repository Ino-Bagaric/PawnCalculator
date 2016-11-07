#include <a_samp>
#include <zcmd>
#include <sscanf2>
#include <calculator>


CMD:calculate(playerid, arg[])
{
	new 
		compute[64], 
		result, 
		bool:fail, 
		error[24],
		str[64]
	;
	if (!sscanf(arg, "s[64]", compute))
	{
		TryCalculate(compute, result, fail, error, sizeof(error));
		if(!fail)
		{
			format (str, sizeof(str), "Calculated: %d", result);
			SendClientMessage(playerid, -1, str);
		}
		else
		{
			format (str, sizeof(str), "Calculate Error: %s", error);
			SendClientMessage(playerid, -1, str);
		}
	}
	else SendClientMessage(playerid, -1, "Usage: /calculate [anything]");
	return 1;
}