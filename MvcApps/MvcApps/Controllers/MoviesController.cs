using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using MvcApps.Models;

namespace MvcApps.Controllers
{
    public class MoviesController : Controller
    {
        //
        // GET: /Movies/ random

        public ActionResult Random()
        {
            var movie = new Movies()
            {
                name = "Mon bosena Porar table e",
                director = "Meshu",
                releaseYear = "11-11-2014"
            };
            return View(movie);
        }

    }
}
