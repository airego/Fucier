using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace Kuafoo.Model
{
    public class ProcessMap
    {
        public int ProcessId { get; set; }
        public string Message { get; set; }
        public string Command { get; set; }
        public DataReceivedEventHandler Handller { get;set; }
        public void Start(string e = "cmd.exe", string workdir = ".")
        {
            var process = new Process();
            process.StartInfo.FileName = e;
            process.StartInfo.WorkingDirectory = workdir;
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardInput = true;
            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.CreateNoWindow = true;
            process.OutputDataReceived += Handller;
            process.Start();
            ProcessId = process.Id;
            process.StandardInput.WriteLine(Command);
            process.BeginOutputReadLine();
        }
        public void Kill()
        {
            Process.GetProcessById(ProcessId).Kill();
        }
        public void State() { }
    }
}
