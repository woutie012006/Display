using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Diagnostics;
namespace CNCForm
{
    
    public class Administration
    {
        List<Instruction> instructions = new List<Instruction>();

        private void SaveToBinary(string path)
        {
            using (Stream fileStream = new FileStream(path, FileMode.Create,
                           FileAccess.Write, FileShare.None))
            {
                IFormatter formatter = new BinaryFormatter();
                formatter.Serialize(fileStream, instructions);
            }
        }

        private void OpenFromBinary(string path)
        {
            using (Stream fileStream = new FileStream(path, FileMode.Open,
                           FileAccess.Read, FileShare.Read))
            {
                IFormatter formatter = new BinaryFormatter();
                instructions = (List<Instruction>)formatter.Deserialize(fileStream);
            };

        }     
    }
}
