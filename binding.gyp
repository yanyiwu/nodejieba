{
  "targets": [
    {
      "target_name": "segment",
      "sources": [ "./src/segment.cpp" ],
      "cflags": [
        "-DLOGGER_LEVEL=LL_WARN"
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
    }
  ]
}
