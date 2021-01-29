using System;
using System.Collections.Generic;
using System.Text;
using System.Text.Json.Serialization;

namespace Kuafoo.Model
{
    [Serializable]
    public class AppMap
    {
        [JsonPropertyName(name: "app")]
        public Application App { get; set; }
    }
    [Serializable]
    public class Application {
        [JsonPropertyName(name: "workdir")]
        public string WorkDir { get; set; }
        [JsonPropertyName(name: "plugins")]
        public string Plugins { get; set; }
    }
}
