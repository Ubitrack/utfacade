add_subdirectory(src/utFacade)
add_subdirectory(src/utComponents)
ut_install_utql_patterns()

# wrappers and helpers
add_subdirectory(apps/Console)
add_subdirectory(apps/DotNet)
add_subdirectory(apps/Java)

# install custom files
file(GLOB _doc_files LIST_DIRECTORIES false "doc/utqlDoc/*" "doc/utqlDoc/*/*" "doc/utqlDoc/*/*/*")
foreach(pfile ${_doc_files})
  string(REGEX REPLACE "^.*/doc/" "" pfile2 "${pfile}")
  GET_FILENAME_COMPONENT(fpath ${pfile2} PATH)
  IF(fpath)
	install(FILES ${pfile} DESTINATION "${UBITRACK_DOC_INSTALL_DIRECTORY}/${fpath}" COMPONENT doc)
  ELSE(fpath)
    install(FILES ${pfile} DESTINATION "${UBITRACK_DOC_INSTALL_DIRECTORY}" COMPONENT doc)
  ENDIF(fpath)
endforeach()