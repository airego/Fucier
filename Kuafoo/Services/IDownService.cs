using System;
using System.Collections.Generic;
using System.Text;

namespace Kuafoo.Services
{
    public interface IDownService
    {
        public void Download(string url, string dir);
    }
}
