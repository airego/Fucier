using System;
using System.Collections.Generic;
using System.Text;
using static Kuafoo.Service.IDownService;

namespace Kuafoo.Service
{
    public class DownService : IDownService
    {
        public delegate void OnProcessChanged(int val);
        public event OnProcessChanged ProcessChanged;
        public void Download(string url, string dir)
        {
            ProcessChanged(0);



            ProcessChanged(100);
        }
    }
}
