using Kuafoo.Model;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace Kuafoo.Service
{
    public interface IProcessService
    {
        public void Start(ProcessMap map);
        public void Kill();
        public void SetHandler(DataReceivedEventHandler handler);
    }
}
