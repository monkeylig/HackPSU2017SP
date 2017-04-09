package com.jhard.hackpsu2017sp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.github.mikephil.charting.charts.ScatterChart;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.ScatterData;
import com.github.mikephil.charting.data.ScatterDataSet;
import com.github.mikephil.charting.interfaces.datasets.IScatterDataSet;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity
{

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ScatterChart chart = (ScatterChart)findViewById(R.id.plot);
        List<Entry> valsComp1 = new ArrayList<Entry>();
        valsComp1.add(new Entry(0, 100000));
        valsComp1.add(new Entry(1, 110000));
        valsComp1.add(new Entry(2, 120000));

        ScatterDataSet setComp1 = new ScatterDataSet(valsComp1, "Company 1");
        setComp1.setAxisDependency(YAxis.AxisDependency.RIGHT);
        List<IScatterDataSet> dataSets = new ArrayList<>();
        dataSets.add(setComp1);
        chart.setData(new ScatterData(dataSets));

    }
}
