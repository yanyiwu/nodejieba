{
  "targets": [
    {
      "target_name": "nodejieba",
      "sources": ["./lib/index.cpp", "./lib/nodejieba.cpp"],
      "cflags": [
        "-DLOGGING_LEVEL=WARNING"
      ],
      'configurations': {
        'Release': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'ExceptionHandling': '1',
              'PreprocessorDefinitions': ['LOGGING_LEVEL=WARNING'],
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
              "-DLOGGING_LEVEL=WARNING",
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
