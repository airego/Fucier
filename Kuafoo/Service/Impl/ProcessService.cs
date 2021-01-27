using Kuafoo.Model;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace Kuafoo.Service
{
    public class ProcessService : IProcessService
    {
        private ProcessMap processMap { get; set; }
        public DataReceivedEventHandler Handller { get; set; }
        public void Start(ProcessMap map)
        {
            processMap = map;
            var process = new Process();
            process.StartInfo.FileName = processMap.App;
            process.StartInfo.WorkingDirectory = processMap.WorkDir;
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardInput = true;
            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.CreateNoWindow = true;
            process.OutputDataReceived += Handller;
            process.Start();
            processMap.ProcessId = process.Id;
            process.StandardInput.WriteLine(processMap.Command);
            process.BeginOutputReadLine();
        }
        public void Kill()
        {
            Process.GetProcessById(processMap.ProcessId).Kill();
        }
        public void State()
        {
            // Process.GetProcessById(processMap.ProcessId).Threads[0].ThreadState;
        }
        public void SetHandler(DataReceivedEventHandler handler)
        {
            Handller = handler;
        }
    }
}
