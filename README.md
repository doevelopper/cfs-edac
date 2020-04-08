[![GitHub Actions status](https://github.com/doevelopper/cfs-edac/workflows/C++%20CI%20Workflow/badge.svg)](https://github.com/doevelopper/cfs-osal/actions)

Also, the logger has to be given a default level (***INFO*** is used by default otherwise), and destinations have to be attached to the log engine (no destination is attached by default).

## Levels

As for any respectable logging facility, messages are associated to a level, which allows classification and later filtering of log messages.

| Level | Definition |
|:-----:|:-----------|
| **FATAL**| Severe errors that cause premature termination. |
| **ERROR**| Runtime errors or unexpected conditions. |
| **WARN** | Use of deprecated APIs, undesirable but not necessarily wrong runtimes situations. |
| **INFO** | Interesting runtime events. |
| **DEBUG**| Detailed information on the flow through the system. |
| **TRACE**| More detailed information about the code path. |

These levels are addressed by choosing the relevant entry point in dtk log’s interface.

Note that these level form a hierarchy. If dtk’s logging level is set to *TRACE*, all logs will be visible, unless set to *WARN*, only *WARN*, *ERROR* and *FATAL* log messages will be visible.

