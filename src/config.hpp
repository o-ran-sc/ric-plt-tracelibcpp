#ifndef _TRACELIB_CONFIG_HPP_
#define _TRACELIB_CONFIG_HPP_

#include <boost/algorithm/string.hpp>
#include <jaegertracing/Tracer.h>

#define TRACING_ENABLED_ENV      "TRACING_ENABLED"
#define JAEGER_SAMPLER_TYPE_ENV  "TRACING_JAEGER_SAMPLER_TYPE"
#define JAEGER_SAMPLER_PARAM_ENV "TRACING_JAEGER_SAMPLER_PARAM"
#define JAEGER_AGENT_ADDR_ENV    "TRACING_JAEGER_AGENT_ADDR"
#define JAEGER_LOG_LEVEL_ENV     "TRACING_JAEGER_LOG_LEVEL"

namespace tracelibcpp
{
    typedef enum {
        LOG_ALL,
        LOG_ERR,
        LOG_NONE
    } LogLevel;
    class ConfMaker {
    public:
        ConfMaker(std::string serviceName):
            name(serviceName) {}

        std::string getEnv(const char* envName, std::string defVal);

        bool isTracingEnabled(void);

        jaegertracing::Config makeNopTraceConfig(void);

        jaegertracing::samplers::Config getSamplerConfig(void);

        jaegertracing::reporters::Config getReporterConfig(void);

        LogLevel getLoggingLevel(void);

        std::unique_ptr<jaegertracing::logging::Logger> getLogger(void);

        jaegertracing::Config getTraceConfig(void);

    private:
        std::string name;
    };
}

#endif
