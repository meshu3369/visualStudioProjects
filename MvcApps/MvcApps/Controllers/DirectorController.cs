using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using MvcApps.Models;

namespace MvcApps.Controllers
{
    public class DirectorController : Controller
    {
        //
        // GET: /Director/

        public ActionResult Index()
        {
            var director = new Director()
            {
                director_name = "meshu",
                dob = "1-1-1994",
                best_movie = "hello from the other side"
            };
            return View(director);
        }

    }
}
