// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <winmeta.h>
#include <string>
#include "SimpleTraceLogging.h"

// Define the GUID to use in TraceLoggingProviderRegister 
// {3970F9cf-2c0c-4f11-b1cc-e3a1e9958833}
TRACELOGGING_DEFINE_PROVIDER(
	g_hMyComponentProvider,
	"SimpleTraceLoggingProvider",
	(0x3970f9cf, 0x2c0c, 0x4f11, 0xb1, 0xcc, 0xe3, 0xa1, 0xe9, 0x95, 0x88, 0x33));

void main(int argc, char **argv)
{
	char sampleValue[] = "Sample value";

	// Register the provider
	TraceLoggingRegister(g_hMyComponentProvider);

	// Log an event
	TraceLoggingWrite(g_hMyComponentProvider,
		"StartLogEvent",
		TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
		TraceLoggingValue(sampleValue, "Starting to Log"));


	TraceLoggingWrite(
		g_hMyComponentProvider,
		"SampleEvent",
		TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
		TraceLoggingString("Test Log Message", "Line1"),
		TraceLoggingString("Test Log Message 2", "Line2"));

	try
	{
		int denom = std::stoi("0");
		if (denom == 0)
		{
			throw std::overflow_error("Divide by zero exception");
		}

		int res = 5 / denom;
	}
	catch (const std::exception ex)
	{
		TraceLoggingWrite(
			g_hMyComponentProvider,
			"CalculationTask",
			TraceLoggingLevel(WINEVENT_LEVEL_ERROR),
			TraceLoggingString(ex.what())
		);
	}

	TraceLoggingUnregister(g_hMyComponentProvider);
}
