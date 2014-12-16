{
  "targets": [
    {
      "target_name": "segment",
      "sources": [ "./src/segment.cpp", "./src/mix_segment.cpp", "./src/query_segment.cpp", "./src/pos_tagger.cpp" ],
      "cflags": [
        "-DLOGGER_LEVEL=LL_WARN"
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
    }
  ]
}
