#pragma once

#include <string>
#include <chrono>
#include <iostream>

namespace util {

	class ScopeTimer {
	public:
		ScopeTimer(std::string text = "", unsigned int line = 0, unsigned int iterations = 0) :text(text), line(line), iterations(iterations)
		{
			start = std::chrono::high_resolution_clock::now();
		}

		~ScopeTimer()
		{
			auto end = std::chrono::high_resolution_clock::now();
			auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			long long int ms = static_cast<long long int>(dur.count());

			if (iterations > 2) ms /= iterations;

			if (text.length() > 0) printf("%s ", text);
			if (line > 0) printf("(Line %u) ", line);
			if (iterations > 2) printf("(avg. %u) ", iterations);
			if (text.length() > 0 || line > 0 || iterations > 2) printf(": ");
			printf("%lldms", ms);
			printf("\n");
		}

	protected:
		unsigned int iterations;
		std::string text;
		unsigned int line;
		std::chrono::time_point<std::chrono::high_resolution_clock> start;
	};

#define SCOPETIMER() util::ScopeTimer t(__FUNCTION__, __LINE__, 0)
#define SCOPETIMERAVG(iterations) util::ScopeTimer t(__FUNCTION__, __LINE__,iterations)

}

