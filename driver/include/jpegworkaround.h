/**
  *@file jpegworkaround.h
  *@brief JPEG_MEM_SRC Workaround
  *
  * Workaround for missing jpeg_mem_src
  * Adapted from the actual source for jpeg_mem_src in newer versions of libjpeg
  */
typedef struct {
	struct jpeg_source_mgr pub;   /* public fields */

	FILE * infile;                /* source stream */
	JOCTET * buffer;              /* start of buffer */
	boolean start_of_file;        /* have we gotten any data yet? */
} jsourcemgr;

typedef jsourcemgr *jj_src_ptr;

#define INPUT_BUF_SIZE 4096
#define JFREAD(file,buf,sizeofbuf)  \
  ((size_t) fread((void *) (buf), (size_t) 1, (size_t) (sizeofbuf), (file)))

// Nothing needs to be done for the memory source
METHODDEF(void) jj_init_mem_src(j_decompress_ptr cinfo) {
	return;
}

// Or to terminate the source
METHODDEF(void) jj_term_source(j_decompress_ptr cinfo) {
	return;
}

// Fill the input buffer
METHODDEF(boolean) jj_fill_mem_input_buffer(j_decompress_ptr cinfo) {
    jj_src_ptr src = (jj_src_ptr) cinfo->src;
  	size_t nbytes;

  	nbytes = JFREAD(src->infile, src->buffer, 4096);

	// If we're out of data, let the user know
  	if (nbytes <= 0) {
		if (src->start_of_file) {     /* Treat empty input file as fatal error */
			printf("Empty input file\n");
			return FALSE;
		}
		printf("Premature end of JPEG file\n");
    		/* Insert a fake EOI marker */
    		src->buffer[0] = (JOCTET) 0xFF;
		src->buffer[1] = (JOCTET) JPEG_EOI;
		nbytes = 2;
	}

	src->pub.next_input_byte = src->buffer;
	src->pub.bytes_in_buffer = nbytes;
	src->start_of_file = FALSE;

	return TRUE;
}

// Skip unwanted data in the stream
METHODDEF(void) jj_skip_input_data (j_decompress_ptr cinfo, long num_bytes) {
	struct jpeg_source_mgr * src = cinfo->src;

	/* Just a dumb implementation for now.  Could use fseek() except
	 * it doesn't work on pipes.  Not clear that being smart is worth
	 * any trouble anyway --- large skips are infrequent.
	 */
	if (num_bytes > 0) {
		while (num_bytes > (long) src->bytes_in_buffer) {
			num_bytes -= (long) src->bytes_in_buffer;
			(void) (*src->fill_input_buffer) (cinfo);
			/* note we assume that fill_input_buffer will never
			 * return FALSE, so suspension need not be handled. */
		}
		src->next_input_byte += (size_t) num_bytes;
		src->bytes_in_buffer -= (size_t) num_bytes;
	}
}

// Fill the fields with the appropriate information for decoding from memory      
int jj_mem_src(j_decompress_ptr cinfo, unsigned char *in, unsigned long sz) {      
    struct jpeg_source_mgr *src;
        
	// Sanity checks
	if(in == NULL || sz == 0)  
		return RI_RESP_FAILURE;
        
	// Allocate the source object
	if(cinfo->src == NULL) 
		cinfo->src = (struct jpeg_source_mgr*) (*cinfo->mem->alloc_small)((j_common_ptr) cinfo, JPOOL_PERMANENT, sizeof(struct jpeg_source_mgr));           
        
	// Setup the decompression routines
	src = cinfo->src;
	src->init_source = jj_init_mem_src;
	src->fill_input_buffer = jj_fill_mem_input_buffer;
	src->skip_input_data = jj_skip_input_data;
	src->resync_to_restart = jpeg_resync_to_restart;
	src->term_source = jj_term_source;
	src->bytes_in_buffer = (size_t) sz;
	src->next_input_byte = (JOCTET *) in;
        
	return RI_RESP_SUCCESS; 
}

// END WORKAROUND
