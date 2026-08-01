add_library(math_engine STATIC)

target_sources(math_engine PUBLIC 
    FILE_SET CXX_MODULES FILES
        linear_algebra.cppm
        path_tracing_objects.cppm
)

target_compile_features(math_engine PUBLIC cxx_std_23)