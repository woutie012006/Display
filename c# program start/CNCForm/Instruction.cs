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
        //Point kan alleen int gebruiken

        //startpoint
        private double x1 {get; set;  }
        private double y1 {get; set; }

        //endpoint
        private double x2 { get; set; }
        private double y2 { get; set; }

        //position of the drill 0 = up and 1 = down (feel free to change this)
        private int position;


        public Instruction(double x1, double y1, double x2, double y2, int position) 
        {
            this.x1 = x1;
            this.y1 = y1;

            this.x2 = x2;
            this.y2 = y2;

            this.position = position;

        }
    }
}
