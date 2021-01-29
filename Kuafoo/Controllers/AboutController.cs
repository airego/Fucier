using Kuafoo.Model;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;

namespace Kuafoo.Controllers
{
    class AboutController
    {
        public AppMap AppMap { get; set; }
        public Views.About.Index Index()
        {
            var page = new Views.About.Index();
            page.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            return page;
        }
    }
}
