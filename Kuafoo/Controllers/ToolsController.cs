using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Kuafoo.Model;
using Kuafoo.Views.Tools;

namespace Kuafoo.Controllers
{
    class ToolsController
    {
        public AppMap AppMap { get; set; }
        public Views.Tools.Index Index()
        {
            var page = new Views.Tools.Index();
            page.AppMap = AppMap;
            return page;
        }
    }
}