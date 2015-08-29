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

        /// <summary>
        /// Inserts the point at the wanted position 
        /// </summary>
        /// <param name="position"></param>
        /// <param name="p"></param>
        /// <returns></returns>
        public bool InsertInstruction(int position, Instruction p)
        {
            try
            {
                List<Instruction> np = new List<Instruction>(); //new Instructions
                for (int i = 0; i < instructions.Count + 1; i++)
                {
                    if (i == position)
                    {
                        np.Add(p);
                    }
                    np.Add(instructions[i]);
                }
                instructions = np;
            }
            catch (Exception e) { Debug.WriteLine(e); return false; }
            return true;
        }

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
