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
            processMap.CurrentProcess = new Process();
            processMap.CurrentProcess.StartInfo.FileName = processMap.App;
            processMap.CurrentProcess.StartInfo.WorkingDirectory = processMap.WorkDir;
            processMap.CurrentProcess.StartInfo.UseShellExecute = false;
            processMap.CurrentProcess.StartInfo.RedirectStandardInput = true;
            processMap.CurrentProcess.StartInfo.RedirectStandardOutput = true;
            processMap.CurrentProcess.StartInfo.CreateNoWindow = true;
            processMap.CurrentProcess.OutputDataReceived += Handller;
            processMap.CurrentProcess.Start();
            processMap.ProcessId = processMap.CurrentProcess.Id;
            processMap.Name = processMap.CurrentProcess.ProcessName;
            processMap.CurrentProcess.StandardInput.WriteLine(processMap.Command);
            processMap.CurrentProcess.BeginOutputReadLine();
        }
        public void Kill()
        {
            processMap.CurrentProcess.Kill(true);
        }
        public bool Status()
            => processMap.CurrentProcess.Responding;
        public void SetHandler(DataReceivedEventHandler handler)
        {
            Handller = handler;
        }
    }
}
