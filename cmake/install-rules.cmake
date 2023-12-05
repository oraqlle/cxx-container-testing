install(
    TARGETS cxx-container-testing
    RUNTIME COMPONENT cxx-container-testing_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
