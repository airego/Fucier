using System;
using System.Collections.Generic;
using System.Text;

namespace Kuafoo.Service
{
    public interface IDownService
    {
        public void Download(string url, string dir);
    }
}
