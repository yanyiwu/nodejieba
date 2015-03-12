{
  "targets": [
    {
      "target_name": "segment",
      "sources": [ "./src/segment.cpp", "./src/mix_segment.cpp", "./src/query_segment.cpp", "./src/pos_tagger.cpp" , "./src/keyword_extractor.cpp"],
      "cflags": [
        "-DLOGGER_LEVEL=LL_WARN"
      ],
      'configurations': {
        'Release': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'ExceptionHandling': '1',
              'PreprocessorDefinitions': ['LOGGER_LEVEL=LL_WARN'],
            }
          }
        }
      },
	  "conditions": [
	  	[ "OS == 'mac'", {
		  "xcode_settings": {
			"OTHER_CPLUSPLUSFLAGS":[
			  "-mmacosx-version-min=10.7",
			  "-std=c++11",
			  "-stdlib=libc++"
			]
		  }
		}],
	  ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
    }
  ]
}
