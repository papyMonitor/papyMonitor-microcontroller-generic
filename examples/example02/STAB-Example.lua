--TYPES USED BY SERIAL MONITOR
--typecfg enum {
--	eComDataType_Float		= 'f', -- 8 chars
--	eComDataType_U32 		= 'W', -- 8 chars
--	eComDataType_I32 		= 'w', -- 8 chars
--	eComDataType_U16 		= 'I', -- 4 chars
--	eComDataType_I16 		= 'i', -- 4 chars
--	eComDataType_U8 		= 'B', -- 2 chars
--	eComDataType_I8 		= 'b', -- 2 chars
--} eComDataType_t--

---------------  CONFIGURATION ---------------------- 
cfg:Default({
    ----------------------
    -- Mandatory fields --
    ----------------------    
    Baudrate = 460800,

    -- Commands from monitor to target;
    SetValue = '#',
    ReportValueOn = '?',
    ReportValueOff = '!',

    -- Messages from target to monitor
    IReportValue =        ':',
    IReportTextConsole =  '>',

    --Every sampleTimeHW a variable is sent
    SampleTimeHW= 0.001,

    --- LAYOUT
    GroupTabs= { 
        {-- group0
            --NoExpandX=true,
            Tabs = {
                { -- Tab0
                    TabName="Base",
                    Columns= {
                        { 0, 9, },
                        { 10, },
                    }
                },
                { -- Tab1
                    TabName="Arm 0",
                    Columns= {
                        { 20, 29, },
                        { 30, },
                    }
                },
                { -- Tab2
                    TabName="Arm 1",
                    Columns= {
                        { 40, 49, },
                        { 50, },
                    }
                },
                { -- Tab3
                    TabName="Arm 2",
                    Columns= {
                        { 60, 69, },
                        { 70, },
                    }
                },    
                { -- Tab4
                    TabName="Pick tool",
                    Columns= {
                        { 80, 89, },
                        { 90, },
                    }
                },                             
            },
        },
        {-- group1
            --NoExpandX=true,
            Tabs = {
                { -- Tab0
                    TabName="Table",
                    Columns= {
                        { 100 },          
                    }                 
                },                              
            }
        }, 
        {-- group2
            NoExpandX=true,
            Tabs = {           
                { -- Tab1
                    TabName="Others",
                    Columns= {
                        { 115, }, 
                        { 116, }, 
                        { 117, 118, },                                      
                    }  
                } 
            }            
        },            
        {-- group3
            NoExpandX=true,
            Tabs = {
                { -- Tab0
                    TabName="Commands",
                    Columns= {
                        { 119, 120, 121 }
                    }                 
                }
            }
        },
    },

    ----------------------
    -- Optional fields  --
    ---------------------- 
    Endian=     'little',   -- default = 'little'
    Vue3D=      true,       -- default = 'false'
    Plot=       true,       -- default = 'false'
})

---------------  VARIABLES ----------------------

--------------- 
cfg:Variable({
    Name="Base values",
    Type="f",
    Index=0,
    Data= {
        { SingleText = "PID P value" },
        { SingleText = "PID I value" },
        { SingleText = "PID D value" },
        { SingleText = "FeedF value" },
        { SingleText = "Set   value", CanEdit=true },
        { SingleText = "PID Control" },
        { SingleText = "Simul square", CanEdit=true },
        { SingleText = "Simul sq velo", CanEdit=true },
        { SingleText = "System filter", CanEdit=true },
    }
})
cfg:Variable({
    Name="Base value",
    Type="f",
    Index=9,
    Data= {
        { CanPlot=true },
    }
})

--------------- 
cfg:Variable({
    Name="Base parameters",
    Type="f",
    Index=10,
    Parameter="Base parameters",
    Data= {
        { SingleText = "PID Kp", Precision = 4, CanEdit=true },
        { SingleText = "PID Ki", Precision = 4, CanEdit=true },
        { SingleText = "PID Kd", Precision = 4, CanEdit=true },
        { SingleText = "PID I Limit min", Precision = 4, CanEdit=true },
        { SingleText = "PID I Limit max", Precision = 4, CanEdit=true },
        { SingleText = "PID Control limit min", Precision = 4, CanEdit=true },
        { SingleText = "PID Control limit max", Precision = 4, CanEdit=true },
        { SingleText = "PID D tau", Precision = 4, CanEdit=true },
        { SingleText = "FeedF coefficient", Precision = 4, CanEdit=true },
    }
})

--------------- 
cfg:Variable({
    Name="Arm 0 values",
    Type="f",
    Index=20,
    Data= {
        { SingleText = "PID P value" },
        { SingleText = "PID I value" },
        { SingleText = "PID D value" },
        { SingleText = "FeedF value" },
        { SingleText = "Set   value", CanEdit=true },
        { SingleText = "PID Control" },
        { SingleText = "Simul square", CanEdit=true },
        { SingleText = "Simul sq velo", CanEdit=true },
        { SingleText = "System filter", CanEdit=true },
    }
})
cfg:Variable({
    Name="Arm 0 value",
    Type="f",
    Index=29,
    Data= {
        { CanPlot=true },
    }
})

--------------- 
cfg:Variable({
    Name="Arm 1 parameters",
    Type="f",
    Index=30,
    Parameter="Arm 1 parameters",
    Data= {
        { SingleText = "PID Kp", Precision = 4, CanEdit=true },
        { SingleText = "PID Ki", Precision = 4, CanEdit=true },
        { SingleText = "PID Kd", Precision = 4, CanEdit=true },
        { SingleText = "PID I Limit min", Precision = 4, CanEdit=true },
        { SingleText = "PID I Limit max", Precision = 4, CanEdit=true },
        { SingleText = "PID Control limit min", Precision = 4, CanEdit=true },
        { SingleText = "PID Control limit max", Precision = 4, CanEdit=true },
        { SingleText = "PID D tau", Precision = 4, CanEdit=true },
        { SingleText = "FeedF coefficient", Precision = 4, CanEdit=true },
    }
})

--------------- 
cfg:Variable({
    Name="Arm 2 values",
    Type="f",
    Index=40,
    Data= {
        { SingleText = "PID P value" },
        { SingleText = "PID I value" },
        { SingleText = "PID D value" },
        { SingleText = "FeedF value" },
        { SingleText = "Set   value", CanEdit=true },
        { SingleText = "PID Control" },
        { SingleText = "Simul square", CanEdit=true },
        { SingleText = "Simul sq velo", CanEdit=true },
        { SingleText = "System filter", CanEdit=true },
    }
})
cfg:Variable({
    Name="Arm 2 value",
    Type="f",
    Index=49,
    Data= {
        { CanPlot=true },
    }
})

--------------- 
cfg:Variable({
    Name="Arm 2 parameters",
    Type="f",
    Index=50,
    Parameter="Arm 2 parameters",
    Data= {
        { SingleText = "PID Kp", Precision = 4, CanEdit=true },
        { SingleText = "PID Ki", Precision = 4, CanEdit=true },
        { SingleText = "PID Kd", Precision = 4, CanEdit=true },
        { SingleText = "PID I Limit min", Precision = 4, CanEdit=true },
        { SingleText = "PID I Limit max", Precision = 4, CanEdit=true },
        { SingleText = "PID Control limit min", Precision = 4, CanEdit=true },
        { SingleText = "PID Control limit max", Precision = 4, CanEdit=true },
        { SingleText = "PID D tau", Precision = 4, CanEdit=true },
        { SingleText = "FeedF coefficient", Precision = 4, CanEdit=true },
    }
})

--------------- 
cfg:Variable({
    Name="Arm 3 values",
    Type="f",
    Index=60,
    Data= {
        { SingleText = "PID P value" },
        { SingleText = "PID I value" },
        { SingleText = "PID D value" },
        { SingleText = "FeedF value" },
        { SingleText = "Set   value", CanEdit=true },
        { SingleText = "PID Control" },
        { SingleText = "Simul square", CanEdit=true },
        { SingleText = "Simul sq velo", CanEdit=true },
        { SingleText = "System filter", CanEdit=true },
    }
})
cfg:Variable({
    Name="Arm 3 value",
    Type="f",
    Index=69,
    Data= {
        { CanPlot=true },
    }
})

--------------- 
cfg:Variable({
    Name="Arm 3 parameters",
    Type="f",
    Index=70,
    Parameter="Arm 3 parameters",
    Data= {
        { SingleText = "PID Kp", Precision = 4, CanEdit=true },
        { SingleText = "PID Ki", Precision = 4, CanEdit=true },
        { SingleText = "PID Kd", Precision = 4, CanEdit=true },
        { SingleText = "PID I Limit min", Precision = 4, CanEdit=true },
        { SingleText = "PID I Limit max", Precision = 4, CanEdit=true },
        { SingleText = "PID Control limit min", Precision = 4, CanEdit=true },
        { SingleText = "PID Control limit max", Precision = 4, CanEdit=true },
        { SingleText = "PID D tau", Precision = 4, CanEdit=true },
        { SingleText = "FeedF coefficient", Precision = 4, CanEdit=true },
    }
})

--------------- 
cfg:Variable({
    Name="Pick tool values",
    Type="f",
    Index=80,
    Data= {
        { SingleText = "PID P value" },
        { SingleText = "PID I value" },
        { SingleText = "PID D value" },
        { SingleText = "FeedF value" },
        { SingleText = "Set   value", CanEdit=true },
        { SingleText = "PID Control" },
        { SingleText = "Simul square", CanEdit=true },
        { SingleText = "Simul sq velo", CanEdit=true },
        { SingleText = "System filter", CanEdit=true },
    }
})
cfg:Variable({
    Name="Pick tool value",
    Type="f",
    Index=89,
    Data= {
        { CanPlot=true },
    }
})

--------------- 
cfg:Variable({
    Name="Pick tool parameters",
    Type="f",
    Index=90,
    Parameter="Pick tool parameters",
    Data= {
        { SingleText = "PID Kp", Precision = 4, CanEdit=true },
        { SingleText = "PID Ki", Precision = 4, CanEdit=true },
        { SingleText = "PID Kd", Precision = 4, CanEdit=true },
        { SingleText = "PID I Limit min", Precision = 4, CanEdit=true },
        { SingleText = "PID I Limit max", Precision = 4, CanEdit=true },
        { SingleText = "PID Control limit min", Precision = 4, CanEdit=true },
        { SingleText = "PID Control limit max", Precision = 4, CanEdit=true },
        { SingleText = "PID D tau", Precision = 4, CanEdit=true },
        { SingleText = "FeedF coefficient", Precision = 4, CanEdit=true },
    }
})
--------------- 
cfg:Variable({
    Name="Table",
    Type="f",
    Index=100,
    Parameter="Table parameters",
    Data= {
        { SingleText = "Param 0", Precision = 4, CanEdit=true },
        { SingleText = "Param 1", Precision = 4, CanEdit=true },
        { SingleText = "Param 2", Precision = 4, CanEdit=true },
        { SingleText = "Param 3", Precision = 4, CanEdit=true },
        { SingleText = "Param 4", Precision = 4, CanEdit=true },
        { SingleText = "Param 5", Precision = 4, CanEdit=true },
        { SingleText = "Param 6", Precision = 4, CanEdit=true },
        { SingleText = "Param 7", Precision = 4, CanEdit=true },
        { SingleText = "Param 8", Precision = 4, CanEdit=true },
        { SingleText = "Param 9", Precision = 4, CanEdit=true },
        { SingleText = "Param 10", Precision = 4, CanEdit=true },
        { SingleText = "Param 11", Precision = 4, CanEdit=true },
    }
})

--------------- 
cfg:Variable({
    Name="Simulation",
    Type="B",
    Index=115,
    Data= {
        { -- Data0
            BoolsOnU8=true,
            BitsTexts = {
                "simulSquareCH0", "simulSquareCH1",  
                "simulSquareCH2", "simulSquareCH3",
                "simulSquareCH4",   "Not used",      
                "Not used",    "Not used"
            },
            CanBitsEdits = {
                true,true,true,true,
                true,false,false,false
            },
        }
    }
})

--------------- 
cfg:Variable({
    Name="Status 1",
    Type="B",
    Index=116,
    Data= {
        { -- Data0
            BoolsOnU8=true,
            BitsTexts = {
                "out0", "out1",  
                "out2", "out3",
                "in0",  "in1",      
                "in2",   "in3"
            },
            CanBitsEdits = {
                true,true,true,true,
            },
        }
    }
})

--------------- 
cfg:Variable({
    Name="Byte 0",
    Type="B",
    Index=117,
    Data= {
        {
            CanEdit = true;
        }
    }
})

--------------- 
cfg:Variable({
    Name="Byte 1",
    Type="B",
    Index=118,
})

---------------
cfg:Variable({
    Name="Save params to FLASH",
    Type="B",
    Index=119,
    HideData=true,
    WidgetType="Button",
})

---------------
cfg:Variable({
    Name="Report all variables ON",
    Type="B",
    Index=120,
    HideData=true,
    WidgetType="Button",
})

---------------
cfg:Variable({
    Name="Report all variables OFF",
    Type="B",
    Index=121,
    HideData=true,
    WidgetType="Button",
})


---------------
cfg:Solid({
    Name="Sol",
    Body="Cube",

    StartPosition = { 0, 0, 0 },
    Color = { 0.0, 0.0, 0.0 },
    CubeSize = { 5, 0.1, 10 },
    Formula = 
        function(self)
            -- 
        end,   
    Parent="Root",  
 })


---------------
cfg:Solid({
    Name="Base",
    Body="Cylinder",
    CylinderTopRadius = 0.8,
    CylinderBottomRadius = 1.0,
    CylinderHeight=0.2,

    StartPosition={ 0, 0.1, 0 },
    Color={ 0.4, 0.3, 0.4 },
    Formula = 
        function(self)
            --self.R.y = - self:GetVariable(8)
        end,       
    Parent="Sol",
})

cfg:Solid({
    Name="Bras0",
    Body="Cylinder",
    CylinderTopRadius = 0.3,
    CylinderBottomRadius = 0.3,
    CylinderHeight=2,

    StartPosition={ 0, 0.01, 0 },
    StartRotation={ 0, 180, 0 },
    Color={ 0.3, 0.4, 0.3 },
    MoveRotationSmooth=true,
    Formula = 
        function(self)
            self.R.y = self:GetVariable(9)
        end,     
    Parent="Base",  
})

cfg:Solid({
    Name="Artic0",
    Body="Sphere",
    SphereRadius = 0.4,
    SphereHeight = 0.8,

    StartPosition={ 0, 2, 0 },
    Color={ 0.6, 0.4, 0 },
    MoveRotationSmooth=true,
    Formula = 
        function(self)
            --
        end,       
    Parent="Bras0",        
})

cfg:Solid({
    Name="Bras1",
    Body="Cylinder",
    CylinderTopRadius = 0.2,
    CylinderBottomRadius = 0.25,
    CylinderHeight=2,

    StartRotation={ -70, 0, 0 },
    Color={ 0.4, 0.1, 0.2 },
    MoveRotationSmooth=true,
    Formula = 
        function(self)
            self.R.x = - self:GetVariable(29)
        end,
    Parent="Artic0",
})

cfg:Solid({
    Name="Artic1",
    Body="Sphere",
    SphereRadius = 0.32,
    SphereHeight = 0.64,

    StartPosition={ 0, 2, 0 },
    Color={ 0.6, 0.4, 0.0 },
    MoveRotationSmooth=true,
    Formula = 
        function(self)
            --
        end,       
    Parent="Bras1",        
})

cfg:Solid({
    Name="Bras2",
    Body="Cylinder",
    CylinderTopRadius = 0.15,
    CylinderBottomRadius = 0.15,
    CylinderHeight=1.5,

    StartRotation={ -70, 0, 0 },
    Color={ 0.5, 0.6, 0.7 },
    MoveRotationSmooth=true,
    Formula = 
        function(self)
            self.R.x = self:GetVariable(49)
        end,
    Parent="Artic1",
})

cfg:Solid({
    Name="Artic3",
    Body="Sphere",
    SphereRadius = 0.25,
    SphereHeight = 0.50,

    StartPosition={ 0, 1.5, 0 },
    Color={ 0.6, 0.4, 0.0 },
    MoveRotationSmooth=true,
    Formula = 
        function(self)
          --self.R.y = self:GetVariable(69)
        end,       
    Parent="Bras2",        
})

cfg:Solid({
    Name="Bras3",
    Body="Cube",
    CubeSize={0.3, 0.7, 0.3},

    StartPosition={ 0, 0.1, 0 },
    Color={ 0.3, 0.3, 0.3 },
    MoveRotationSmooth=true,
    Formula = 
        function(self)
          self.R.y = self:GetVariable(69)
        end,       
    Parent="Artic3",        
})

cfg:Solid({
    Name="PinceA1",
    Body="Cylinder",
    CylinderTopRadius = 0.01,
    CylinderBottomRadius = 0.05,
    CylinderHeight=0.7,   

    StartPosition={ 0, 0.6, 0.15 },
    StartRotation={ 10, 0, 0 },
    Color={ 0.2, 0.2, 0.2 },
    MoveRotationSmooth=true,
    Formula = 
        function(self)
            self.R.x = - self:GetVariable(89)
        end,
    Parent="Bras3",
})

cfg:Solid({
    Name="PinceA2",
    Body="Cylinder",
    CylinderTopRadius = 0.01,
    CylinderBottomRadius = 0.05,
    CylinderHeight=0.7,   

    StartPosition={ 0, 0.6, -0.15 },
    StartRotation={ -10, 0, 0 },
    Color={ 0.2, 0.2, 0.2 },
    MoveRotationSmooth=true,
    Formula = 
        function(self)
            self.R.x =  self:GetVariable(89)
        end,
    Parent="Bras3",
})
