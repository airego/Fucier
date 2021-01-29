using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace Kuafoo.Model
{
    public class ProcessMap
    {
        public string Command { get; set; }
        public string App { get; set; } = "cmd.exe";
        public string WorkDir { get; set; } = ".";
        public Process CurrentProcess { get; set; }
    }
}
