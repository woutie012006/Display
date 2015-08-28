using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Diagnostics;

namespace CNCForm
{
    [Serializable]
    public class Instruction
    {
        List<Point> points {get; set;}
        
        public Instruction(List<Point> points ) 
        { 
            this.points = points;
        }

        /// <summary>
        /// Inserts the point at the wanted position 
        /// </summary>
        /// <param name="position"></param>
        /// <param name="p"></param>
        /// <returns></returns>
        public bool InsertInstruction(int position, Point p)
        {
            try 
            { 
                List<Point> np = new List<Point>(); //newPoints
                for(int i = 0; i< points.Count+1;i++)
                {
                    if(i == position)
                    {
                        np.Add(p);
                    }
                    np.Add(points[i]);
                }
                points = np;
            }
            catch (Exception e) { Debug.WriteLine(e); return false; }
            return true;
        }
    }
}
