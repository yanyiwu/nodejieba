{
  "targets": [
    {
      "target_name": "nodejieba",
      "sources": ["./lib/index.cpp", "./lib/nodejieba.cpp"],
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
			  "-stdlib=libc++",
              "-DLOGGER_LEVEL=LL_WARN",
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
