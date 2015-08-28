using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
namespace CNCForm
{
    //i like administration classes though it could be redundant for now.
    public class Administration
    {
        Instruction  instruction = new Instruction(new List<Point>());

        private void SaveToBinary(string path)
        {
            using (Stream fileStream = new FileStream(path, FileMode.Create,
                           FileAccess.Write, FileShare.None))
            {
                IFormatter formatter = new BinaryFormatter();
                formatter.Serialize(fileStream, instruction);
            }
        }

        private void OpenFromBinary(string path)
        {
            using (Stream fileStream = new FileStream(path, FileMode.Open,
                           FileAccess.Read, FileShare.Read))
            {
                IFormatter formatter = new BinaryFormatter();
                instruction = (Instruction)formatter.Deserialize(fileStream);
            };

        }     
    }
}
