/*
 *
 * CS61C Spring 2013 Project 2: Small World
 *
 * Partner 1 Name:
 * Partner 1 Login:
 *
 * Partner 2 Name:
 * Partner 2 Login:
 *
 * REMINDERS: 
 *
 * 1) YOU MUST COMPLETE THIS PROJECT WITH A PARTNER.
 * 
 * 2) DO NOT SHARE CODE WITH ANYONE EXCEPT YOUR PARTNER.
 * EVEN FOR DEBUGGING. THIS MEANS YOU.
 *
 */

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;
import java.lang.Math;
import java.util.*;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.input.SequenceFileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.SequenceFileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;


public class SmallWorld {
    // Maximum depth for any breadth-first search
    public static final int MAX_ITERATIONS = 20;

    // Example writable type
    public static class EValue implements Writable {

        public int exampleInt; //example integer field
        public long[] exampleLongArray; //example array of longs

        public EValue(int exampleInt, long[] exampleLongArray) {
            this.exampleInt = exampleInt;
            this.exampleLongArray = exampleLongArray;
        }

        public EValue() {
            // does nothing
        }

        // Serializes object - needed for Writable
        public void write(DataOutput out) throws IOException {
            out.writeInt(exampleInt);

            // Example of serializing an array:
            
            // It's a good idea to store the length explicitly
            int length = 0;

            if (exampleLongArray != null){
                length = exampleLongArray.length;
            }

            // always write the length, since we need to know
            // even when it's zero
            out.writeInt(length);

            // now write each long in the array
            for (int i = 0; i < length; i++){
                out.writeLong(exampleLongArray[i]);
            }
        }

        // Deserializes object - needed for Writable
        public void readFields(DataInput in) throws IOException {
            // example reading an int from the serialized object
            exampleInt = in.readInt();

            // example reading length from the serialized object
            int length = in.readInt();

            // Example of rebuilding the array from the serialized object
            exampleLongArray = new long[length];
            
            for(int i = 0; i < length; i++){
                exampleLongArray[i] = in.readLong();
            }

        }

        public String toString() {
            // We highly recommend implementing this for easy testing and
            // debugging. This version just returns an empty string.
            return new String();
        }

    }


    /* The first mapper. Part of the graph loading process, currently just an 
     * identity function. Modify as you wish. */
    public static class LoaderMap extends Mapper<LongWritable, LongWritable, 
        LongWritable, LongWritable> {

        @Override
        public void map(LongWritable key, LongWritable value, Context context)
                throws IOException, InterruptedException {

            // example of getting value passed from main
            int inputValue = Integer.parseInt(context.getConfiguration().get("inputValue"));


            context.write(key, value);
        }
    }


    /* The first reducer. This is also currently an identity function (although it
     * does break the input Iterable back into individual values). Modify it
     * as you wish. In this reducer, you'll also find an example of loading
     * and using the denom field.  
     */
    public static class LoaderReduce extends Reducer<LongWritable, LongWritable, 
        LongWritable, LongWritable> {

        public long denom;

        public void reduce(LongWritable key, Iterable<LongWritable> values, 
            Context context) throws IOException, InterruptedException {
            // We can grab the denom field from context: 
            denom = Long.parseLong(context.getConfiguration().get("denom"));

            // You can print it out by uncommenting the following line:
            // System.out.println(denom);

            // Example of iterating through an Iterable
            for (LongWritable value : values){            
                context.write(key, value);
            }
        }

    }


    // ------- Add your additional Mappers and Reducers Here ------- //
















    public static void main(String[] rawArgs) throws Exception {
        GenericOptionsParser parser = new GenericOptionsParser(rawArgs);
        Configuration conf = parser.getConfiguration();
        String[] args = parser.getRemainingArgs();

        // Pass in denom command line arg:
        conf.set("denom", args[2]);

        // Sample of passing value from main into Mappers/Reducers using
        // conf. You might want to use something like this in the BFS phase:
        // See LoaderMap for an example of how to access this value
        conf.set("inputValue", (new Integer(5)).toString());

        // Setting up mapreduce job to load in graph
        Job job = new Job(conf, "load graph");

        job.setJarByClass(SmallWorld.class);

        job.setMapOutputKeyClass(LongWritable.class);
        job.setMapOutputValueClass(LongWritable.class);
        job.setOutputKeyClass(LongWritable.class);
        job.setOutputValueClass(LongWritable.class);

        job.setMapperClass(LoaderMap.class);
        job.setReducerClass(LoaderReduce.class);

        job.setInputFormatClass(SequenceFileInputFormat.class);
        job.setOutputFormatClass(SequenceFileOutputFormat.class);

        // Input from command-line argument, output to predictable place
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path("bfs-0-out"));

        // Actually starts job, and waits for it to finish
        job.waitForCompletion(true);

        // Repeats your BFS mapreduce
        int i = 0;
        while (i < MAX_ITERATIONS) {
            job = new Job(conf, "bfs" + i);
            job.setJarByClass(SmallWorld.class);

            // Feel free to modify these four lines as necessary:
            job.setMapOutputKeyClass(LongWritable.class);
            job.setMapOutputValueClass(LongWritable.class);
            job.setOutputKeyClass(LongWritable.class);
            job.setOutputValueClass(LongWritable.class);

            // You'll want to modify the following based on what you call
            // your mapper and reducer classes for the BFS phase.
            job.setMapperClass(Mapper.class); // currently the default Mapper
            job.setReducerClass(Reducer.class); // currently the default Reducer

            job.setInputFormatClass(SequenceFileInputFormat.class);
            job.setOutputFormatClass(SequenceFileOutputFormat.class);

            // Notice how each mapreduce job gets gets its own output dir
            FileInputFormat.addInputPath(job, new Path("bfs-" + i + "-out"));
            FileOutputFormat.setOutputPath(job, new Path("bfs-"+ (i+1) +"-out"));

            job.waitForCompletion(true);
            i++;
        }

        // Mapreduce config for histogram computation
        job = new Job(conf, "hist");
        job.setJarByClass(SmallWorld.class);

        // Feel free to modify these two lines as necessary:
        job.setMapOutputKeyClass(LongWritable.class);
        job.setMapOutputValueClass(LongWritable.class);

        // DO NOT MODIFY THE FOLLOWING TWO LINES OF CODE:
        job.setOutputKeyClass(LongWritable.class);
        job.setOutputValueClass(LongWritable.class);

        // You'll want to modify the following based on what you call your
        // mapper and reducer classes for the Histogram Phase
        job.setMapperClass(Mapper.class); // currently the default Mapper
        job.setReducerClass(Reducer.class); // currently the default Reducer

        job.setInputFormatClass(SequenceFileInputFormat.class);
        job.setOutputFormatClass(TextOutputFormat.class);

        // By declaring i above outside of loop conditions, can use it
        // here to get last bfs output to be input to histogram
        FileInputFormat.addInputPath(job, new Path("bfs-"+ i +"-out"));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));

        job.waitForCompletion(true);
    }
}
