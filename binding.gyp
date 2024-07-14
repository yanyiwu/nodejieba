{
  "targets": [
    {
      "target_name": "nodejieba",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "xcode_settings": { "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++",
        "MACOSX_DEPLOYMENT_TARGET": "10.7",
      },
      "msvs_settings": {
        "VCCLCompilerTool": { "ExceptionHandling": 1 },
      },
      "win_delay_load_hook": "true",
      "sources": ["./lib/index.cpp", "./lib/nodejieba.cpp"],
      "cflags": [
        "-DLOGGING_LEVEL=LL_WARNING"
      ],
      "include_dirs" : [
        "<!(node -p \"require('node-addon-api').include_dir\")",
        "./deps"
      ],
      'configurations': {
        'Release': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'ExceptionHandling': '1',
              'PreprocessorDefinitions': ['LOGGING_LEVEL=LL_WARNING'],
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
              "-DLOGGING_LEVEL=LL_WARNING",
			]
		  }
		}],
	  ],
    }
  ]
}
