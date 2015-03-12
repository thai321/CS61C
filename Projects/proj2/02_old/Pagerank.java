/* 

Welcome to the scaffolding for CS61c's Project 2, Fall 2011!

The code below is set up to iteratively calculate the Pagerank of a graph, where
the graph is defined as a tab- and comma-delimited text file, one parent-node per line.
This file is pointed to by the user as an argument from the command line.
The algorithm's implementation involves repeated calls to MapReduce via Hadoop.
The intermediate results are stored in directories ./temp0 through ./temp[NUM_ROUNDS-1], before
the final, sorted results are stored in the user-provided output directory (also provided
as a command line argument). 

***
IMPORTANT
Since the graph is recreated at each iteration, you should either:
1) make sure your disc quota has enough room for [NUM_ROUNDS] additional copies of your input graph file.
or 
2) find a clever rewrite to main() such that fewer distinct copies are needed for successful computation.
Please contact Brian Gawalt (gawalt@eecs) or Eric Liang (ekhliang@eecs) with questions.
This code comes thanks to the generosity of Ari Rabkin, Charles Reiss, and Michael Armbrust.
***

The main function should not need much if any attention, though there are a pair of handy debugging 
booleans you can toggle to control whether sorting or combining are performed.

Do remember that you should not let another project team copy your code, and similarly,
any code you submit here should be the product of your partnership alone.

*/

import java.io.IOException;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.SequenceFileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.SequenceFileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

/* Though we found a way to implement Pagerank using only the above libraries, feel free
    to include the additional libraries of your choice here. */

public class Pagerank
{   
    // Modify these according to the assignment's instructions
    private static double ALPHA = 0.15;  // Our "wildcard!" parameter
    private static int NUM_ROUNDS = 10; // Should be > 1/ALPHA for good convergence
    
    public static class PRMap extends Mapper<LongWritable, Text, Text, Text>
    {
        private Text keyword = new Text();
        private Text valword = new Text();
        public void map(LongWritable lineNum, Text line, Context context) throws IOException, InterruptedException
        {
            // Err, um... just a bit of quick bookkeepping to get the input KV pairs formatted right...
            if (line.toString().length() == 0) {
                return;
            }
            Text key = new Text();
            Text value = new Text();
            StringTokenizer spline = new StringTokenizer(line.toString(),"\t");
            key.set(spline.nextToken());  // Key of type Text
            value.set(spline.nextToken());  // Value of type Text
            // Phew! That's better. Use "key" and "value" as if they were the mapper's original arguments.
            
            /* Input Key: Name of Node (str)
             Input Value: Comma separated values, in the order
                    Node's current PR value (float)
                    Message flag (either "NODE" or "MSG")
                    Number of nodes total (int)
                    first child's name (str)
                    second child's name (str)
                    ....
                    last child's name (str)                 
            */
            
            /* Your Code Here */
          
            /* Output Key/Value: Your choice. */
        }
    }
    
    public static class PRCombine extends Reducer<Text, Text, Text, Text> {
      
      @Override 
      public void reduce(Text key, Iterable<Text> values,
              Context context) throws IOException, InterruptedException {
            /* Your Code Here. */
      }
    }
    
    public static class PRReduce extends Reducer<Text,Text,Text,Text>
    {
        private Text result = new Text();
        public void reduce(Text key, Iterable<Text> values,
        Context context) throws IOException, InterruptedException
        {
            /* Input Key/Value: Your choice. */
            
            /* Your Code Here. */
            
            
            /* Output Key: Name of Node (str)
             Output Value: Comma separated values, in the order
                    Node's NEW, UPDATED PR value (float)
                    Message flag (either "NODE" or "MSG")
                    Number of nodes total (int)
                    first child's name (str)
                    second child's name (str)
                    ....
                    last child's name (str)                 
            */
        }
        
    }
    
    
    public static class SortMap extends Mapper<LongWritable, Text, DoubleWritable, Text>
    {
        private Text keyword = new Text();
        private DoubleWritable valword = new DoubleWritable();
        public void map(LongWritable lineNum, Text line, Context context) throws IOException, InterruptedException
        {
            /* Input Key: Name of Node (str)
             Input Value: Comma separated values, in the order
                    Node's current PR value (float)
                    Message flag (either "NODE" or "MSG")
                    Number of nodes total (int)
                    first child's name (str)
                    second child's name (str)
                    ....
                    last child's name (str)                 
            */
            if (line.toString().length() == 0) {
                return;
            }
            
            Text key = new Text();
            Text value = new Text();
            StringTokenizer spline = new StringTokenizer(line.toString(),"\t");
            key.set(spline.nextToken());  // Key of type Text
            value.set(spline.nextToken());  // Value of type Text
            
            /* Your Code Here */
            
            /* Output Key/Value: Your choice. */
            
        }
    }
    
     public static class SortReduce extends Reducer<DoubleWritable,Text,Text,Text>
    {
        private Text word = new Text();
        public void reduce(DoubleWritable key, Iterable<Text> values,
        Context context) throws IOException, InterruptedException
        {
            /* Input Key/Value: Your choice. */
            
            /* Your code here. */
            
            /* Output Key: Name of node
                Output Value: Node's (final) Pagerank value */
        }
    }
    
    
    public static void main(String[] args) throws Exception
    {   
        // Some handy flags for debugging. Turn on and off combining or sorting.
        boolean doCombine = false;
        boolean doSort = true;
        // Note that without sorting, final output lives in "temp[NUM_ROUNDS-1]"

        Configuration conf = new Configuration();
        
        // First iteration: Munge on [user-specified input file], store results in ./temp0
        
        Job job = new Job(conf, "pagerank_itr0");
        job.setJarByClass(Pagerank.class);      // In what class are our map/reduce functions for this job found?
        job.setMapperClass(PRMap.class);        // What is our map function for this job?
        job.setReducerClass(PRReduce.class);    // What is our reduce function for this job?
        if(doCombine) job.setCombinerClass(PRCombine.class); // May or may not be combining.
        
        job.setOutputKeyClass(Text.class);              // What are the (hadoop.io compliant) datatype for our
        job.setOutputValueClass(Text.class);            // reducer output's key-value pairs?
        job.setInputFormatClass(TextInputFormat.class);     // How will the mapper distinguish (key-value) record inputs?
        FileInputFormat.addInputPath(job, new Path(args[0])); // First command line argument
        FileOutputFormat.setOutputPath(job, new Path("temp0"));
        job.waitForCompletion(true);
        
        for (int i = 0; i < (NUM_ROUNDS-1); i++) {
            // Consecutive iterations: Munge on ./temp[i], store results in ./temp[i+1]
            job = new Job(conf, "pagerank_itr"+(i+1));
            job.setJarByClass(Pagerank.class);
            job.setMapperClass(PRMap.class);
            job.setReducerClass(PRReduce.class);
            if(doCombine) job.setCombinerClass(PRCombine.class); // May or may not be combining.
            
            job.setOutputKeyClass(Text.class);
            job.setOutputValueClass(Text.class);
            job.setInputFormatClass(TextInputFormat.class);
            FileInputFormat.addInputPath(job, new Path("temp"+i)); 
            FileOutputFormat.setOutputPath(job, new Path("temp"+(i+1)));
            job.waitForCompletion(true);
        }
        
        // Final MapReduce job: Munge on ./temp[NUM_ROUNDS-1], store results in [user provided output directory]
        if(doSort) {
            job = new Job(conf, "sort");
            job.setJarByClass(Pagerank.class);
            job.setMapperClass(SortMap.class);
            job.setReducerClass(SortReduce.class);
        
            job.setMapOutputKeyClass(DoubleWritable.class);
            job.setOutputKeyClass(Text.class);
            job.setOutputValueClass(Text.class);
            job.setInputFormatClass(TextInputFormat.class);
            FileInputFormat.addInputPath(job, new Path("temp"+(NUM_ROUNDS-1))); 
            FileOutputFormat.setOutputPath(job, new Path(args[1]));  // Second command line argument
        
            job.waitForCompletion(true);
        }
        
    }
}
